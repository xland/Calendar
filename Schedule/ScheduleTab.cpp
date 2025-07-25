#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QUuid>

#include "ScheduleTab.h"
#include "Util.h"
#include "Eventer.h"
#include "DialogList.h"
#include "../Data/ScheduleModel.h"
#include "../Data/Schedules.h"

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
    QRect addRect(width()-28, 4, 28, 22);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setBrush(QColor(200, 220, 240));
    p.setPen(Qt::NoPen);
    p.drawRect(rect().adjusted(0,0,2,0));

    p.setBrush(QColor(255, 255, 255));
    p.setFont(Util::getTextFont(13));
    if (isCurDayTab) {
        p.drawRect(curRect);
        p.setBrush(Qt::NoBrush);
        p.setPen(QColor(30, 30, 30));
        p.drawText(curRect, Qt::AlignCenter, "当日日程");
        p.setPen(hoverIndex == 1 ? QColor(30, 30, 30) : QColor(120, 120, 120));
        p.drawText(allRect, Qt::AlignCenter, "全部日程");
    }
    else {
        p.drawRect(allRect);
        p.setBrush(Qt::NoBrush);
        p.setPen(QColor(30, 30, 30));
        p.drawText(allRect, Qt::AlignCenter, "全部日程");
        p.setPen(hoverIndex == 0 ? QColor(30, 30, 30) : QColor(120, 120, 120));
        p.drawText(curRect, Qt::AlignCenter, "当日日程");
    }
    if (hoverIndex == 2) {
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(255, 255, 255));
        p.drawRoundedRect(addRect,2,2);
    }
    p.setFont(Util::getIconFont(13));
    p.setPen(QColor(80, 80, 80));
    p.setBrush(Qt::NoBrush);
    p.drawText(addRect, Qt::AlignCenter, QChar(0xe647));
}

void ScheduleTab::mouseMoveEvent(QMouseEvent* event)
{
    auto pos = event->position().toPoint();
    auto index{ -1 };
    if (!isCurDayTab && pos.x() > 0 && pos.x() < rw) {
        setCursor(Qt::PointingHandCursor);
        index = 0;
    }
    else if (isCurDayTab && pos.x() > rw && pos.x() < 2 * rw) {
        setCursor(Qt::PointingHandCursor);
        index = 1;
    }
    else if (QRect(width() - 28, 4, 28, 22).contains(pos)) {
        setCursor(Qt::PointingHandCursor);
        index = 2;
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
        emit Eventer::get()->schedulesChange();
    }
    else if (!isCurDayTab && hoverIndex == 0) {
        isCurDayTab = true;
        update();
        emit Eventer::get()->schedulesChange();
    }
    else if (hoverIndex == 2) {
        addNew();
    }
}

void ScheduleTab::addNew()
{
    //auto p = (DialogList*)topLevelWidget();
    //QDateTime dateTime(p->curDay,QTime::currentTime());
    //long long timestamp = dateTime.toSecsSinceEpoch();
    //Schedules::get()->cancelSelecte();
    //emit Eventer::get()->schedulesChange();
}

