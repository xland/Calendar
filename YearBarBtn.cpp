#include <QPaintEvent>
#include <QPainter>

#include "Skin.h"
#include "Util.h"
#include "YearBarBtn.h"

YearBarBtn::YearBarBtn(const uint& code, QWidget* parent) : YearBarBtnBase(parent), code{code}
{
}

YearBarBtn::~YearBarBtn()
{
	
}

void YearBarBtn::paintEvent(QPaintEvent* event)
{
    YearBarBtnBase::paintEvent(event);
    QPainter painter(this);
    auto r = rect().adjusted(16, 2, -14, -2);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setFont(Util::getIconFont(12));
    auto skin = Skin::get();
    painter.setPen(skin->yearBtn);
    painter.drawText(r, Qt::AlignCenter, QChar(code));
}
