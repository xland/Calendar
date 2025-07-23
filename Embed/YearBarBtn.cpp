#include <QPaintEvent>
#include <QPainter>

#include "Skin.h"
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
    auto skin = Skin::get();
    painter.setFont(Util::getIconFont(14));
    if (isHover) {
        painter.setBrush(skin->yearBtnHover);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
        painter.setPen(QColor(60,60,60));
    }
    else {
        painter.setPen(skin->yearBtn);
    }
    painter.drawText(rect(), Qt::AlignCenter, QChar(code));
}
