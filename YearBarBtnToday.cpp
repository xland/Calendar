#include <QPaintEvent>
#include <QPainter>

#include "Skin.h"
#include "Util.h"
#include "YearBarBtnToday.h"

YearBarBtnToday::YearBarBtnToday(QWidget* parent) : YearBarBtnBase(parent)
{
    auto skin = Skin::get();
}

YearBarBtnToday::~YearBarBtnToday()
{
	
}

void YearBarBtnToday::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    auto skin = Skin::get();
    auto r = rect();
    if (isHover) {
        painter.setBrush(skin->yearBtnHover);
        painter.setPen(Qt::NoPen);
        painter.drawRect(r);
    }
    painter.setPen(skin->yearBtn);
    painter.setBrush(Qt::NoBrush);
    auto font = Util::getTextFont(12);
    painter.setFont(*font);
    painter.drawText(r, Qt::AlignCenter, "今");

}