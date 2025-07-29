#include <QPaintEvent>
#include <QPainter>

#include "Util.h"
#include "YearBarBtn.h"

YearBarBtn::YearBarBtn(const uint& code, QWidget* parent) : BtnBase(parent), code{code}
{
    setFixedSize(26, 22);
}

YearBarBtn::~YearBarBtn()
{
	
}

void YearBarBtn::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setFont(Util::getIconFont(14));
    if (isHover) {
        painter.setBrush(QColor(255, 255, 255, 76));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
        painter.setPen(QColor(60,60,60));
    }
    else {
        painter.setPen(QColor(90, 90, 90));
    }
    painter.drawText(rect(), Qt::AlignCenter, QChar(code));
}
