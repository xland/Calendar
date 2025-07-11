#include <QPaintEvent>
#include <QPainter>

#include "MainWindow.h"
#include "TipInfo.h"
#include "Skin.h"
#include "Util.h"
#include "YearBarBtnBase.h"

YearBarBtnBase::YearBarBtnBase(QWidget* parent) : BtnBase(parent)
{
	setFixedSize(48, 22);
    setMouseTracking(true);
    setCursor(Qt::CursorShape::PointingHandCursor);
}

YearBarBtnBase::~YearBarBtnBase()
{
	
}

void YearBarBtnBase::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    auto r = rect().adjusted(16, 2, -14, -2);
    auto skin = Skin::get();
    if (isHover) {
        painter.setBrush(skin->yearBtnHover);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(r);
    }
    painter.setBrush(Qt::NoBrush);
    painter.setPen(skin->yearBtnBorder);
    painter.drawEllipse(r);
}
