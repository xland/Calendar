#include "WindowMain.h"

WindowMain::WindowMain() {
    long w{ 1200 }, h{ 800 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
    InitWindow(x, y, w, h, L"°²×°³ÌÐò");
}
WindowMain::~WindowMain() {

}

void WindowMain::OnPaint() {
    //PaintCtx->fillBox(0, 0, 400, h, BLRgba32(253, 233, 235));
}

bool WindowMain::CaptionTest(const int& x, const int& y) {
    if (x > 0 && x < w - 104 && y>0 && y < 56) {
        return true;
    }
    else
    {
        return false;
    }
}
void WindowMain::ProcessWindowMsg(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

}