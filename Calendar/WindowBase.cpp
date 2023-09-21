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
    delete PaintCtx;
    delete CanvasImage;
    DeleteDC(compatibleDC);
    DeleteObject(bitmap);
}


void WindowBase::InitWindow(const int& x, const int& y, const long& w, const long& h, const std::wstring& title)
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
    wcx.lpfnWndProc = &WindowBase::RouteWindowMessage;
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
    hwnd = CreateWindowEx(NULL, wcx.lpszClassName, title.c_str(),
        WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    const MARGINS shadowState{ 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadowState);
    InitCanvas();
    ChangeCursor(IDC_ARROW);
}
void WindowBase::Show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    Repaint();
}

void WindowBase::InitCanvas() {
    auto stride = w * 4;
    pixelDataSize = stride * h;
    pixelData = new unsigned char[pixelDataSize];
    PaintCtx = new BLContext();
    CanvasImage = new BLImage();
    CanvasImage->createFromData(w, h, BL_FORMAT_PRGB32, pixelData, stride, BL_DATA_ACCESS_RW, [](void* impl, void* externalData, void* userData) {
        delete[] externalData;
        });
    HDC hdc = GetDC(hwnd);
    compatibleDC = CreateCompatibleDC(NULL);
    bitmap = CreateCompatibleBitmap(hdc, w, h); //创建一副与当前DC兼容的位图
    DeleteObject(SelectObject(compatibleDC, bitmap));
    ReleaseDC(hwnd, hdc);
}
void WindowBase::Repaint()
{
    PaintCtx->begin(*CanvasImage);
    PaintCtx->clearAll();
    BLGradient linear(BLLinearGradientValues(0, 0, 0, 460));
    linear.addStop(0.0, BLRgba32(0xFF6cbef8));
    linear.addStop(1.0, BLRgba32(0xFF047af4));
    PaintCtx->fillBox(16, 16, w - 16, 460, linear);
    PaintCtx->fillBox(16, 460, w - 16, h - 16, BLRgba32(0xFFf1f1f1));
    PaintCtx->setFillStyle(BLRgba32(0xFFffffff));
    auto str = ConvertToUTF8(this->title);
    auto font = Font::Get()->fontText;
    font->setSize(19);
    PaintCtx->fillUtf8Text(BLPoint(32, 44), *font, str.c_str());
    OnPaint();
    PaintCtx->end();
    HDC hdc = GetDC(hwnd);
    BITMAPINFO info = { sizeof(BITMAPINFOHEADER), w, 0 - h, 1, 32, BI_RGB, pixelDataSize, 0, 0, 0, 0 };
    SetDIBits(hdc, bitmap, 0, h, pixelData, &info, DIB_RGB_COLORS); //使用指定的DIB颜色数据来设置位图中的像素
    BLENDFUNCTION blend = { .BlendOp{AC_SRC_OVER},.SourceConstantAlpha{255},.AlphaFormat{AC_SRC_ALPHA} };//按通道混合
    POINT pSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    UpdateLayeredWindow(hwnd, hdc, NULL, &sizeWnd, compatibleDC, &pSrc, NULL, &blend, ULW_ALPHA);//更新分层窗口
    ReleaseDC(hwnd, hdc);
}
LRESULT CALLBACK WindowBase::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<WindowBase*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (obj) {
        obj->ProcessWindowMsg(hWnd, msg, wParam, lParam);
        return obj->WindowProc(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WindowBase::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
    case WM_SETCURSOR: {
        return true;
    }
    case WM_RBUTTONDOWN: {
        auto x = GET_X_LPARAM(lParam);
        auto y = GET_Y_LPARAM(lParam);
        return OnRightButtonDown(x, y);
    }
    case WM_LBUTTONDOWN: {
        IsLeftBtnDown = true;
        auto x = GET_X_LPARAM(lParam);
        auto y = GET_Y_LPARAM(lParam);
        return OnLeftButtonDown(x, y);
    }
    case WM_LBUTTONUP: {
        IsLeftBtnDown = false;
        auto x = GET_X_LPARAM(lParam);
        auto y = GET_Y_LPARAM(lParam);
        return OnLeftButtonUp(x, y);
    }
    case WM_MOUSELEAVE:
    {
        mouseTracing = false;
        OnMouseMove(INT_MIN, INT_MIN);
        return true;
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
        OnMouseMove(x, y);
        return true;
    }
    case WM_EXITSIZEMOVE: {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        this->x = rect.left;
        this->y = rect.top;
        return true;
    }
    case WM_NCHITTEST:
    {
        auto x = GET_X_LPARAM(lParam) - this->x;
        auto y = GET_Y_LPARAM(lParam) - this->y;
        if (x < 16 || y < 16 || x>w - 16 || y>h - 16) {
            return HTNOWHERE;
        }
        auto flag = OnHitTest(x, y);
        if (flag == HTCAPTION) {
            ChangeCursor(IDC_ARROW);
        }
        return flag;
    }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}