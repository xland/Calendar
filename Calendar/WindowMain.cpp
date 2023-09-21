#include "WindowMain.h"

WindowMain::WindowMain() {
    long w{ 1000 }, h{ 580 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
    InitWindow(x, y, w, h, L"°²×°³ÌÐò");
}
WindowMain::~WindowMain() {

}

void WindowMain::OnPaint() {

}

int WindowMain::OnHitTest(const int& x, const int& y) {
    if (x > 16 && x < w - 104 && y>16 && y < 56) {
        return HTCAPTION;
    }
    else
    {
        return HTCLIENT;
    }
}