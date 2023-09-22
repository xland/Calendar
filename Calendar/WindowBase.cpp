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
    hwnd = CreateWindowEx(NULL, wcx.lpszClassName, title.c_str(),
        WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    const MARGINS shadowState{ 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadowState);
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
    static BITMAPINFO info = { sizeof(BITMAPINFOHEADER), w, 0 - h, 1, 32, BI_RGB, pixelDataSize, 0, 0, 0, 0 };
    HDC hdc = GetDC(hwnd);
    bitmap = CreateDIBSection(hdc, &info, DIB_RGB_COLORS, reinterpret_cast<void**>(&pixelData), NULL, NULL);
    ReleaseDC(hwnd, hdc);

    paintCtx = new BLContext();
    canvasImage = new BLImage();
    canvasImage->createFromData(w, h, BL_FORMAT_PRGB32, pixelData, stride, BL_DATA_ACCESS_RW);
}
void WindowBase::repaint()
{
    paintCtx->begin(*canvasImage);
    paintCtx->clearAll();
    paintCtx->fillBox(0, 0, w, h, BLRgba32(0xFFFFFFFF));
    onPaint();
    for (const auto& item : widgets) {
        item->paint(paintCtx);
    }
    auto str = ConvertToUTF8(this->title);
    auto font = Font::Get()->fontText;
    font->setSize(19);
    paintCtx->fillUtf8Text(BLPoint(16, 28), *font, str.c_str());
    paintCtx->end();
    InvalidateRect(hwnd, nullptr, false);
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
    else
    {
        if (y >= rect.top && y < (rect.top + span)) {
            return HTTOP;
        }
        else if (y > rect.bottom - span && y <= rect.bottom) {
            return HTBOTTOM;
        }
        else if (isPosInCaption(x - rect.left, y - rect.top)) {
            return HTCAPTION;
        }
    }
    return HTCLIENT;
}
POINT WindowBase::pointToClient(LPARAM lParam) {
    POINT p{ GET_X_LPARAM(lParam) ,GET_Y_LPARAM(lParam) };
    ScreenToClient(hwnd, &p);
    return p;
}
void WindowBase::paintToClient() {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HDC hdcBmp = CreateCompatibleDC(hdc);
    DeleteObject(SelectObject(hdcBmp, bitmap));
    BitBlt(hdc, 0, 0, (int)w, (int)h, hdcBmp, 0, 0, SRCCOPY);
    DeleteDC(hdcBmp);
    EndPaint(hwnd, &ps);
    ValidateRect(hwnd, NULL);
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
    case WM_PAINT: {
        paintToClient();
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
        auto p = pointToClient(lParam);
        for (const auto& item : widgets) {
            if (item->isMouseEnter) {
                item->MouseDown(p.x, p.y);
                break;
            }            
        }
        break;
    }
    case WM_LBUTTONUP: {
        isLeftBtnDown = true;
        auto p = pointToClient(lParam);
        for (const auto& item : widgets) {
            if (item->isMouseEnter) {
                item->MouseUp(p.x, p.y);
                break;
            }
        }
        break;
    }
    case WM_MOUSELEAVE:
    {
        mouseTracing = false;
        for (const auto& item : widgets) {
            item->MouseMove(INT_MIN, INT_MIN);
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
        auto p = pointToClient(lParam);
        for (const auto& item : widgets) {
            item->MouseMove(p.x, p.y);
        }
        break;
    }
    case WM_EXITSIZEMOVE: {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        this->x = rect.left;
        this->y = rect.top;
        break;
    }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}