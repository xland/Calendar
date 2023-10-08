#include "ViewCalendar.h"
#include "WindowBase.h"
#include "Util.h"
#include "Font.h"

ViewCalendar::ViewCalendar(WindowBase* parent) :ViewBase(parent) {

}
ViewCalendar::~ViewCalendar() {

}
void ViewCalendar::paint(BLContext* paintCtx) {
    auto str = ConvertToUTF8(L"一 二 三 四 五 六 日");
    auto font = Font::Get()->fontText;
    font->setSize(18.0);
    paintCtx->setFillStyle(BLRgba32(0XFF666666));
    paintCtx->fillUtf8Text(BLPoint(32, 94), *font, str.c_str());
}

std::shared_ptr<ViewCalendar> ViewCalendar::createCalendar(WindowBase* parent) {
    auto calendar = std::make_shared<ViewCalendar>(parent);
    calendar->box = BLBoxI(parent->w - 148, 16, parent->w - 104, 58);
    calendar->foregroundColor = BLRgba32(0xff888888);
    calendar->backgroundColor = BLRgba32(0x00ffffff);
    calendar->onMouseOut = [](ViewBase* sender) {
        sender->backgroundColor = BLRgba32(0x00ffffff);
        sender->parent->repaint();
        sender->isMouseEnter = false;
        };
    calendar->onMouseEnter = [](ViewBase* sender) {
        sender->backgroundColor = BLRgba32(0xffEEEEEE);
        sender->parent->repaint();
        sender->isMouseEnter = true;
        };
    calendar->onMouseUp = [](ViewBase* sender) {
        sender->mouseMove(INT_MIN, INT_MIN);
        ShowWindow(sender->parent->hwnd, SW_SHOWMINIMIZED);
        };
    return calendar;
}