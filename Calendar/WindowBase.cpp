#include "WindowBase.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <thread>
#include <map>
std::map<HWND, WindowBase*> WindowBase::wndMap;

namespace {     
    static WNDPROC SFMLWndProc;
    static int HitTest(const POINT& mousePos,const HWND& hwnd) {
        RECT winRect;
        if (!GetWindowRect(hwnd, &winRect)) {
            return HTNOWHERE;
        }
        static const unsigned borderWidth{ 6 };
        if (mousePos.x < winRect.left + borderWidth && mousePos.y < winRect.top + borderWidth) {
            return HTTOPLEFT;
        }
        else if (mousePos.x > winRect.right - borderWidth && mousePos.y < winRect.top + borderWidth) {
            return HTTOPRIGHT;
        }
        else if (mousePos.x > winRect.right - borderWidth && mousePos.y > winRect.bottom - borderWidth) {
            return HTBOTTOMRIGHT;
        }
        else if (mousePos.x < winRect.left + borderWidth && mousePos.y > winRect.bottom - borderWidth) {
            return HTBOTTOMLEFT;
        }
        else if (mousePos.x < winRect.left + borderWidth) {
            return HTLEFT;
        }
        else if (mousePos.y < winRect.top + borderWidth) {
            return HTTOP;
        }
        else if (mousePos.x > winRect.right - borderWidth) {
            return HTRIGHT;
        }
        else if (mousePos.y > winRect.bottom - borderWidth) {
            return HTBOTTOM;
        }
        else {
            tgui::Vector2<int> pos{ mousePos.x - winRect.left,mousePos.y - winRect.top };
            auto obj = WindowBase::wndMap[hwnd];
            if (obj->isPosInCaption(mousePos, winRect)) {
                return HTCAPTION;
            }
            return HTCLIENT;
        }
    }
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        switch (msg) {
        case WM_NCCALCSIZE:
        {
            if (wparam == TRUE)
            {
                return false;
            }
            break;
        }
        case WM_NCHITTEST: {
            POINT cursor{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
            return HitTest(cursor, hwnd);
            break;
        }
        }
        return CallWindowProc(SFMLWndProc, hwnd, msg, wparam, lparam);
    }
}



WindowBase::WindowBase() {
    
}
WindowBase::~WindowBase() {
}
void WindowBase::initWindow() {
    sfWin = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "MyWin");
    hwnd = sfWin->getNativeHandle();
    SFMLWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
        SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    const MARGINS shadowState{ 0,0,0,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadowState);
    
}