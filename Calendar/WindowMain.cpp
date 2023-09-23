#include "WindowMain.h"
#include "ViewButtonIcon.h"
#include <memory>

WindowMain::WindowMain() {
    long w{ 1200 }, h{ 800 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
    initWindow(x, y, w, h, L"×ÀÃæÈÕÀú");
    views.push_back(ViewButtonIcon::createMinimizeBtn(this));
    views.push_back(ViewButtonIcon::createMaximizeRestoreBtn(this));
    views.push_back(ViewButtonIcon::createCloseBtn(this));
}
WindowMain::~WindowMain() {

}

void WindowMain::onPaint() {
    paintCtx->fillBox(16, 16, 480, h-16, BLRgba32(253, 233, 235));
}

bool WindowMain::isPosInCaption(const int& x, const int& y) {
    if (x > 0 && x < w - 164 && y>0 && y < 56) {
        return true;
    }
    else
    {
        return false;
    }
}