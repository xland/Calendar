#include "WindowBase.h"
#include <format>
#include <windowsx.h>
#include <dwmapi.h>
#include "resource.h"
#include "Util.h"
#include "Font.h"

WindowBase::WindowBase() {
}
WindowBase::~WindowBase() {
    DeleteObject(bitmap);
    DeleteDC(compatibleDC);
    delete paintCtx;
    delete canvasImage;
}

void WindowBase::initWindow(const int& x, const int& y, const long& w, const long& h, const std::wstring& title)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->title = title;
    static int num = 0;
    std::wstring className = std::format(L"Calender_{}", num++);
    auto hinstance = GetModuleHandle(NULL);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &WindowBase::routeWindowMessage;
    wcx.cbWndExtra = sizeof(WindowBase*);
    wcx.hInstance = hinstance;
    //wcx.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON));
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = className.c_str();
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"注册窗口类失败", L"系统提示", NULL);
        return;
    }
    hwnd = CreateWindowEx(WS_EX_LAYERED, wcx.lpszClassName, title.c_str(),
        WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    paintCtx = new BLContext();
    compatibleDC = CreateCompatibleDC(NULL);
    initCanvas();
    //ChangeCursor(IDC_ARROW);
}
void WindowBase::show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    repaint();
}

void WindowBase::initCanvas() {
    auto stride = w * 4;
    pixelDataSize = stride * h;
    pixelData = new unsigned char[pixelDataSize];
    canvasImage = new BLImage();
    canvasImage->createFromData(w, h, BL_FORMAT_PRGB32, pixelData, stride, BL_DATA_ACCESS_RW, [](void* impl, void* externalData, void* userData) {
        delete[] externalData;
        });
    HDC hdc = GetDC(hwnd);
    bitmap = CreateCompatibleBitmap(hdc, w, h); //创建一副与当前DC兼容的位图
    DeleteObject(SelectObject(compatibleDC, bitmap));
    ReleaseDC(hwnd, hdc);
}
void WindowBase::repaint()
{
    paintCtx->begin(*canvasImage);
    paintCtx->clearAll();
    drawShadow();
    paintCtx->fillBox(16, 16, w-16, h-16, BLRgba32(0xFFFFFFFF));
    onPaint();
    for (const auto& item : views) {
        item->paint(paintCtx);
    }
    auto str = ConvertToUTF8(this->title);
    auto font = Font::Get()->fontText;
    font->setSize(20.0);
    paintCtx->setFillStyle(BLRgba32(0XFF333333));
    paintCtx->fillUtf8Text(BLPoint(32, 44), *font, str.c_str());
    paintCtx->end();
    HDC hdc = GetDC(hwnd);
    BITMAPINFO info = { sizeof(BITMAPINFOHEADER), w, 0 - h, 1, 32, BI_RGB, pixelDataSize, 0, 0, 0, 0 };
    SetDIBits(hdc, bitmap, 0, h, pixelData, &info, DIB_RGB_COLORS); //使用指定的DIB颜色数据来设置位图中的像素
    BLENDFUNCTION blend = { .BlendOp{AC_SRC_OVER},.SourceConstantAlpha{255},.AlphaFormat{AC_SRC_ALPHA} };//按通道混合
    POINT pSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    UpdateLayeredWindow(hwnd, hdc, NULL, &sizeWnd, compatibleDC, &pSrc, NULL, &blend, ULW_ALPHA);//更新分层窗口
    ReleaseDC(hwnd, hdc);
}
LRESULT CALLBACK WindowBase::routeWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<WindowBase*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (obj) {
        return obj->windowProc(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WindowBase::hitTest(LPARAM lParam) {
    int x{ GET_X_LPARAM(lParam) };
    int y{ GET_Y_LPARAM(lParam) };
    RECT rect;
    GetWindowRect(hwnd, &rect);
    rect.left += 14;
    rect.top += 14;
    rect.right -= 14;
    rect.bottom -= 14;
    int span = 4;
    if (x >= rect.left && x < (rect.left + span)) {
        if (y >= rect.top && y < (rect.top + span)) {
            return HTTOPLEFT;
        }
        else if (y > rect.bottom - span && y <= rect.bottom) {
            return HTBOTTOMLEFT;
        }
        else {
            return HTLEFT;
        }
    }
    else if (x > rect.right - span && x <= rect.right) {
        if (y >= rect.top && y < (rect.top + span)) {
            return HTTOPRIGHT;
        }
        else if (y > rect.bottom - span && y <= rect.bottom) {
            return HTBOTTOMRIGHT;
        }
        else {
            return HTRIGHT;
        }
    }
    else if(y >= rect.top && y < (rect.top + span)) {
        return HTTOP;
    }
    else if (y > rect.bottom - span && y <= rect.bottom) {
        return HTBOTTOM;
    }
    else if (isPosInCaption(x - rect.left, y - rect.top)) {
        return HTCAPTION;
    }
    else if(x >= (rect.left + span) && y >= (rect.top + span) && y <= (rect.bottom - span) && x <= (rect.right - span))
    {
        return HTCLIENT;
    }
    else
    {
        return HTNOWHERE;
    }
}

LRESULT CALLBACK WindowBase::windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool mouseTracing = false;
    switch (msg)
    {
    case WM_NCCALCSIZE:
    {
        if (wParam == TRUE)
        {
            return false;
        }
        break;
    }
    case WM_NCHITTEST:
    {
        return hitTest(lParam);
    }
    case WM_CLOSE: {
        PostQuitMessage(0);
        break;
    }
    //case WM_SETCURSOR: {
    //    return true;
    //}
    case WM_RBUTTONDOWN: {
        break;
    }
    case WM_RBUTTONUP: {
        break;
    }
    case WM_LBUTTONDOWN: {
        isLeftBtnDown = true;
        int x{ GET_X_LPARAM(lParam) };
        int y{ GET_Y_LPARAM(lParam) };
        for (const auto& item : views) {
            if (item->isMouseEnter) {
                item->mouseDown(x, y);
                break;
            }            
        }
        break;
    }
    case WM_LBUTTONUP: {
        isLeftBtnDown = true;
        int x{ GET_X_LPARAM(lParam) };
        int y{ GET_Y_LPARAM(lParam) };
        for (const auto& item : views) {
            if (item->isMouseEnter) {
                item->mouseUp(x, y);
                break;
            }
        }
        break;
    }
    case WM_MOUSELEAVE:
    {
        mouseTracing = false;
        for (const auto& item : views) {
            item->mouseMove(INT_MIN, INT_MIN);
        }
        break;
    }
    case WM_MOUSEMOVE: {
        if (!mouseTracing)
        {
            TRACKMOUSEEVENT tme = {};
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = hWnd;
            mouseTracing = TrackMouseEvent(&tme);
        }
        int x{ GET_X_LPARAM(lParam) };
        int y{ GET_Y_LPARAM(lParam) };
        for (const auto& item : views) {
            item->mouseMove(x, y);
        }
        break;
    }
    case WM_SIZING: {
        DeleteObject(bitmap);
        delete canvasImage;
        int width = this->w;
        int height = this->h;
        RECT* rect = (RECT*)lParam;
        this->x = rect->left;
        this->y = rect->top;
        this->w = rect->right - rect->left;
        this->h = rect->bottom - rect->top;        
        for (const auto& item : views) {
            item->changeSize(width,height);
        }
        initCanvas();
        repaint();
        break;
    }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

void WindowBase::drawShadow()
{
    {//左上
        BLGradient radial(BLRadialGradientValues(16, 16, 16, 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        paintCtx->fillCircle(16, 16, 16, radial);
        paintCtx->setCompOp(BL_COMP_OP_CLEAR);
        paintCtx->setFillStyle(BLRgba32(0xFF000000));
        paintCtx->fillBox(16, 0, 32, 16);
        paintCtx->fillBox(0, 16, 16, 32);
        paintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    {//右上
        BLGradient radial(BLRadialGradientValues(w - 16, 16, w - 16, 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        paintCtx->fillCircle(w - 16, 16, 16, radial);
        paintCtx->setCompOp(BL_COMP_OP_CLEAR);
        paintCtx->setFillStyle(BLRgba32(0xFF000000));
        paintCtx->fillBox(w - 32, 0, w - 16, 16);
        paintCtx->fillBox(w - 16, 16, w, 32);
        paintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    { //右下
        BLGradient radial(BLRadialGradientValues(w - 16, h - 16, w - 16, h - 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        paintCtx->fillCircle(w - 16, h - 16, 16, radial);
        paintCtx->setCompOp(BL_COMP_OP_CLEAR);
        paintCtx->setFillStyle(BLRgba32(0xFF000000));
        paintCtx->fillBox(w - 16, h - 32, w, h - 16);
        paintCtx->fillBox(w - 32, h - 16, w - 16, h);
        paintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    { //左下
        BLGradient radial(BLRadialGradientValues(16, h - 16, 16, h - 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        paintCtx->fillCircle(16, h - 16, 16, radial);
        paintCtx->setCompOp(BL_COMP_OP_CLEAR);
        paintCtx->setFillStyle(BLRgba32(0xFF000000));
        paintCtx->fillBox(16, h - 16, 32, h);
        paintCtx->fillBox(0, h - 32, 16, h - 16);
        paintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    { //上
        BLGradient linear(BLLinearGradientValues(0, 0, 0, 16));
        linear.addStop(0.0, BLRgba32(0x00000000));
        linear.addStop(1.0, BLRgba32(0x22000000));
        paintCtx->fillBox(16, 0, w - 16, 16, linear);
    }
    { //右
        BLGradient linear(BLLinearGradientValues(w - 16, 16, w, 16));
        linear.addStop(0.0, BLRgba32(0x22000000));
        linear.addStop(1.0, BLRgba32(0x00000000));
        paintCtx->fillBox(w - 16, 16, w, h - 16, linear);
    }
    { //下
        BLGradient linear(BLLinearGradientValues(0, h - 16, 0, h));
        linear.addStop(0.0, BLRgba32(0x22000000));
        linear.addStop(1.0, BLRgba32(0x00000000));
        paintCtx->fillBox(16, h - 16, w - 16, h, linear);
    }
    { //左
        BLGradient linear(BLLinearGradientValues(0, 0, 16, 0));
        linear.addStop(0.0, BLRgba32(0x00000000));
        linear.addStop(1.0, BLRgba32(0x22000000));
        paintCtx->fillBox(0, 16, 16, h - 16, linear);
    }
    //PaintCtx->setStrokeWidth(0.8);
    //PaintCtx->strokeBox(16, 16, w - 16, h - 16, BLRgba32(0, 128, 0));
}