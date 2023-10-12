#include "WinCalendar.h"
#include <Windows.h>

WinCalendar::WinCalendar() {
    long w{ 2000 }, h{ 1700 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
    initWindow(x, y, w, h, L"¿¿Æ×");
    show();
}
WinCalendar::~WinCalendar() {

}
void WinCalendar::ctrlReady() {
    navigate(L"https://www.bing.com");
    openDevTools();
}