#include <QPaintEvent>
#include <QPainter>

#include "MainWindow.h"
#include "TipInfo.h"
#include "Skin.h"
#include "Util.h"
#include "YearBarBtnBase.h"

YearBarBtnBase::YearBarBtnBase(QWidget* parent) : BtnBase(parent)
{
	setFixedSize(26, 22);
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
    auto skin = Skin::get();
    if (isHover) {
        painter.setBrush(skin->yearBtnHover);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
    }
}
