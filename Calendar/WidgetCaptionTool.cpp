#include "WidgetCaptionTool.h"

WidgetCaptionTool::WidgetCaptionTool(WindowBase* parent):WidgetBase(parent) {

}
WidgetCaptionTool::~WidgetCaptionTool() {

}
void WidgetCaptionTool::Paint(BLContext* paintCtx) {
    paintCtx->fillBox(box, BackgroundColor);
    BLFont* font = Font::Get()->fontIcon;
    font->setSize(FontSize);
    BLFontMetrics fm = font->metrics();
    BLTextMetrics tm;
    BLGlyphBuffer gb;
    gb.setUtf8Text(Text.c_str());
    font->shape(gb);
    font->getTextMetrics(gb, tm);
    BLPoint point;
    point.x = Box.x0 + ((Box.x1 - Box.x0) - (tm.boundingBox.x1 - tm.boundingBox.x0)) / 2;
    point.y = Box.y0 + fm.ascent + ((Box.y1 - Box.y0) - font->size()) / 2;
    paintCtx->setFillStyle(ForegroundColor);
    paintCtx->fillUtf8Text(point, *font, Text.c_str());
}