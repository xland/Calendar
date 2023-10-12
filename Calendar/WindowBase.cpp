#include "WindowBase.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <thread>
#include <map>
#include "EventBus.h"

std::map<HWND, WindowBase*> WindowBase::wndMap;

namespace {     
    static WNDPROC SFMLWndProc;
    static bool mouseTracing{false};
    static void mouseOutWindowCasecade(tgui::Widget* target) {
        if (target->isContainer()) {
            auto container = (tgui::Container*)target;
            for (auto& child : container->getWidgets()) {
                mouseOutWindowCasecade(child.get());
            }
        }
        else
        {
            if (target->getWidgetName() == "closeBtn") {
                auto a = 1;
            }
            target->mouseNoLongerOnWidget();
            target->updateTime(0);
        }
    }
    static void mouseOutWindow(const HWND& hwnd) {
        auto obj = WindowBase::wndMap[hwnd];        
        for (auto& child : obj->gui->getWidgets()) {
            mouseOutWindowCasecade(child.get());
        }
    }
    static int HitTest(const POINT& mousePos,const HWND& hwnd) {
        RECT winRect;
        if (!GetWindowRect(hwnd, &winRect)) {
            return HTNOWHERE;
        }
        static const int borderWidth{ 6 };
        if (mousePos.x < winRect.left + borderWidth && mousePos.y < winRect.top + borderWidth) {
            //mouseOutWindow(hwnd);
            return HTTOPLEFT;
        }
        else if (mousePos.x > winRect.right - borderWidth && mousePos.y < winRect.top + borderWidth) {
            //mouseOutWindow(hwnd);
            return HTTOPRIGHT;
        }
        else if (mousePos.x > winRect.right - borderWidth && mousePos.y > winRect.bottom - borderWidth) {
            //mouseOutWindow(hwnd);
            return HTBOTTOMRIGHT;
        }
        else if (mousePos.x < winRect.left + borderWidth && mousePos.y > winRect.bottom - borderWidth) {
            //mouseOutWindow(hwnd);
            return HTBOTTOMLEFT;
        }
        else if (mousePos.x < winRect.left + borderWidth) {
            //mouseOutWindow(hwnd);
            return HTLEFT;
        }
        else if (mousePos.y < winRect.top + borderWidth) {
            //mouseOutWindow(hwnd);
            return HTTOP;
        }
        else if (mousePos.x > winRect.right - borderWidth) {
            //mouseOutWindow(hwnd);
            return HTRIGHT;
        }
        else if (mousePos.y > winRect.bottom - borderWidth) {
            //mouseOutWindow(hwnd);
            return HTBOTTOM;
        }
        else {
            tgui::Vector2<int> pos{ mousePos.x - winRect.left,mousePos.y - winRect.top };
            auto obj = WindowBase::wndMap[hwnd];
            if (obj->isPosInCaption(mousePos, winRect)) {
                //mouseOutWindow(hwnd);
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
                    placement.length = sizeof(WINDOWPLACEMENT);
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
                break;
            }
            case WM_MOUSEMOVE: {
                if (!mouseTracing)
                {
                    TRACKMOUSEEVENT tme = {};
                    tme.cbSize = sizeof(TRACKMOUSEEVENT);
                    tme.dwFlags = TME_LEAVE;
                    tme.hwndTrack = hwnd;
                    mouseTracing = TrackMouseEvent(&tme);
                }
                break;
            }
            case WM_MOUSELEAVE: {
                mouseTracing = false;
                mouseOutWindow(hwnd);
                tgui::Timer::scheduleCallback([] {});
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