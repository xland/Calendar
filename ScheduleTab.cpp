#include <QHBoxLayout>
#include <QPushButton>
#include "ScheduleTab.h"
#include "Util.h"

ScheduleTab::ScheduleTab(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(30);
    setMouseTracking(true);
}

ScheduleTab::~ScheduleTab()
{
	
}

void ScheduleTab::paintEvent(QPaintEvent* event)
{
    QRect curRect(0, 0, rw, 30);
    QRect allRect(rw, 0, rw, 30);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QColor(200, 220, 240));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect().adjusted(0,0,2,0));

    painter.setBrush(QColor(255, 255, 255));
    painter.setFont(Util::getTextFont(13));
    if (isCurDayTab) {
        painter.drawRect(curRect);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(30, 30, 30));
        painter.drawText(curRect, Qt::AlignCenter, "当日日程");
        painter.setPen(hoverIndex == 1 ? QColor(30, 30, 30) : QColor(120, 120, 120));
        painter.drawText(allRect, Qt::AlignCenter, "全部日程");
    }
    else {
        painter.drawRect(allRect);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(30, 30, 30));
        painter.drawText(allRect, Qt::AlignCenter, "全部日程");
        painter.setPen(hoverIndex == 0 ? QColor(30, 30, 30) : QColor(120, 120, 120));
        painter.drawText(curRect, Qt::AlignCenter, "当日日程");
    }
}

void ScheduleTab::mouseMoveEvent(QMouseEvent* event)
{
    auto pos = event->position();
    auto index{ -1 };
    if (!isCurDayTab && pos.x() > 0 && pos.x() < rw) {
        setCursor(Qt::PointingHandCursor);
        index = 0;
    }
    else if (isCurDayTab && pos.x() > rw && pos.x() < 2 * rw) {
        setCursor(Qt::PointingHandCursor);
        index = 1;
    }
    else {
        unsetCursor();
        index = -1;
    }
    if (index != hoverIndex) {
        hoverIndex = index;
        update();
    }
}

void ScheduleTab::leaveEvent(QEvent* event)
{
    unsetCursor();
    if (hoverIndex != -1) {
        hoverIndex = -1;
        update();
    }
}

void ScheduleTab::mousePressEvent(QMouseEvent* event)
{
    if (isCurDayTab && hoverIndex == 1) {
        isCurDayTab = false;
        update();
    }
    else if (!isCurDayTab && hoverIndex == 0) {
        isCurDayTab = true;
        update();
    }
}

