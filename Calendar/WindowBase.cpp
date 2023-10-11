#include "WindowBase.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <thread>
#include <map>
#include "EventBus.h"

std::map<HWND, WindowBase*> WindowBase::wndMap;

namespace {     
    static WNDPROC SFMLWndProc;
    static int HitTest(const POINT& mousePos,const HWND& hwnd) {
        RECT winRect;
        if (!GetWindowRect(hwnd, &winRect)) {
            return HTNOWHERE;
        }
        static const int borderWidth{ 6 };
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
                    WINDOWPLACEMENT placement;
                    GetWindowPlacement(hwnd, &placement);
                    if (placement.showCmd == SW_MAXIMIZE) {                        
                        auto monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
                        MONITORINFO monitor_info{};
                        monitor_info.cbSize = sizeof(monitor_info);
                        GetMonitorInfo(monitor, &monitor_info);
                        auto& params = *reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);
                        params.rgrc[0] = monitor_info.rcWork;
                    }
                    return false;
                }
                break;
            }
            case WM_NCHITTEST: {
                POINT cursor{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
                return HitTest(cursor, hwnd);
                break;
            }
            case WM_SIZE: {
                if (wparam == SIZE_MAXIMIZED) {
                    EventBus::emit("maximized");
                }
                else if (wparam == SIZE_RESTORED) {
                    EventBus::emit("restored");
                }
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
    sf::ContextSettings setting;
    setting.antialiasingLevel = 12;
    sfWin = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(1000, 800)), L"日历",sf::Style::Default,setting);
    hwnd = sfWin->getNativeHandle();
    SFMLWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
        SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    const MARGINS shadowState{ 0,0,0,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadowState);
}