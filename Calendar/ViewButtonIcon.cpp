#include "ViewButtonIcon.h"
#include "Font.h"
#include "Util.h"
#include "WindowBase.h"

ViewButtonIcon::ViewButtonIcon(WindowBase* parent):ViewBase(parent) {

}
ViewButtonIcon::~ViewButtonIcon() {

}
void ViewButtonIcon::paint(BLContext* paintCtx) {
    paintCtx->fillBox(box, backgroundColor);
    BLFont* font = Font::Get()->fontIcon;
    font->setSize(fontSize);
    BLFontMetrics fm = font->metrics();
    BLTextMetrics tm;
    BLGlyphBuffer gb;
    gb.setUtf8Text(text.c_str());
    font->shape(gb);
    font->getTextMetrics(gb, tm);
    BLPoint point;
    point.x = box.x0 + ((box.x1 - box.x0) - (tm.boundingBox.x1 - tm.boundingBox.x0)) / 2;
    point.y = box.y0 + fm.ascent + ((box.y1 - box.y0) - font->size()) / 2;
    paintCtx->setFillStyle(foregroundColor);
    paintCtx->fillUtf8Text(point, *font, text.c_str());
}

std::shared_ptr<ViewButtonIcon> ViewButtonIcon::createMinimizeBtn(WindowBase* parent) {
    auto btn = std::make_shared<ViewButtonIcon>(parent);
    btn->box = BLBoxI(parent->w - 104, 16, parent->w - 60, 56);
    btn->text = reinterpret_cast<const char*>(u8"\ue6e7");
    btn->foregroundColor = BLRgba32(0xffffffff);
    btn->backgroundColor = BLRgba32(0x00ffffff);
    btn->onMouseOut = [](ViewBase* sender) {
        sender->backgroundColor = BLRgba32(0x00ffffff);
        sender->parent->repaint();
        };
    btn->onMouseEnter = [](ViewBase* sender) {
        ChangeCursor(IDC_HAND);
        sender->backgroundColor = BLRgba32(0x33ffffff);
        sender->parent->repaint();
        };
    btn->onMouseUp = [](ViewBase* sender) {
        sender->mouseMove(INT_MIN, INT_MIN);
        ShowWindow(sender->parent->hwnd, SW_SHOWMINIMIZED);
        };
    return btn;
}

std::shared_ptr<ViewButtonIcon> ViewButtonIcon::createCloseBtn(WindowBase* parent) {
    auto btn = std::make_shared<ViewButtonIcon>(parent);
    btn->box = BLBoxI(parent->w - 60, 16, parent->w - 16, 56);
    btn->text = reinterpret_cast<const char*>(u8"\ue6e6");
    btn->foregroundColor = BLRgba32(0xffffffff);
    btn->backgroundColor = BLRgba32(0x00ffffff);
    btn->onMouseOut = [](ViewBase* sender) {
        sender->foregroundColor = BLRgba32(0xffffffff);
        sender->backgroundColor = BLRgba32(0x00ffffff);
        sender->parent->repaint();
        };
    btn->onMouseEnter = [](ViewBase* sender) {
        ChangeCursor(IDC_HAND);
        sender->foregroundColor = BLRgba32(0xffb83c4b);
        sender->backgroundColor = BLRgba32(0x33ffffff);
        sender->parent->repaint();
        };
    btn->onMouseUp = [](ViewBase* sender) {
        SendMessage(sender->parent->hwnd, WM_CLOSE, NULL, NULL);
        PostQuitMessage(0);
        };
    return btn;
}