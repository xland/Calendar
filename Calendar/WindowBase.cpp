#include "WindowBase.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace { 
    static WNDPROC SFMLWndProc;
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
            RECT winRect;
            if (!GetWindowRect(hwnd, &winRect)) {
                return HTNOWHERE;
            }
            static const POINT border{
                GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER),
                GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER)
            };
            static const unsigned client{ 0b0000 }, left{ 0b0001 },
                right{ 0b0010 }, top{ 0b0100 }, bottom{ 0b1000 };
            const auto result =
                left * (cursor.x < (winRect.left + border.x)) |
                right * (cursor.x >= (winRect.right - border.x)) |
                top * (cursor.y < (winRect.top + border.y)) |
                bottom * (cursor.y >= (winRect.bottom - border.y));
            switch (result) {
            case left: return HTLEFT;
            case right: return HTRIGHT;
            case top: return HTTOP;
            case bottom: return HTBOTTOM;
            case top | left: return HTTOPLEFT;
            case top | right: return HTTOPRIGHT;
            case bottom | left: return HTBOTTOMLEFT;
            case bottom | right: return HTBOTTOMRIGHT;
            case client: return HTCAPTION;
            default: return HTNOWHERE;
            }
            break;
        }
        }
        return CallWindowProc(SFMLWndProc, hwnd, msg, wparam, lparam);
    }
}



WindowBase::WindowBase() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "MyWin");
    tgui::Gui gui{ window };
    auto hwnd = window.getNativeHandle();
    SFMLWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
        SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    const MARGINS shadowState{ 0,0,0,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadowState);
    gui.mainLoop();
}
WindowBase::~WindowBase() {
}
