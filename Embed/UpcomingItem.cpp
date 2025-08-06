#include "UpcomingItem.h"
#include "../Util.h"
#include "../Data/ScheduleModel.h"
#include "Alert.h"

UpcomingItem::UpcomingItem(const int& i,ScheduleModel* model, QWidget *parent) : BtnBase(parent),index{i},model{ model }
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    model->setParent(this);
    updateTime();
    connect(this, &BtnBase::click, this, &UpcomingItem::itemClick);
}

UpcomingItem::~UpcomingItem()
{
}

void UpcomingItem::itemClick() {
    auto alert = new Alert(model->Id);
    alert->show();
}

void UpcomingItem::updateTime() {
    auto timespan = model->UpcomingTime - QDateTime::currentDateTime().toSecsSinceEpoch();
    timeStr = Util::getTimeStr(timespan);
    update();
}

void UpcomingItem::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    if (isHover) {
        p.setBrush(QColor(255, 255, 255, 153));
        p.setPen(Qt::NoPen);
        p.drawRect(rect());
    }
    p.setBrush(Qt::NoBrush);
    p.setPen(QColor(60,60,60));
    auto r = rect().adjusted(10, 0, -10, 0);
    p.drawText(r,Qt::AlignLeft|Qt::AlignVCenter,model->Schedule);
    p.drawText(r, Qt::AlignRight | Qt::AlignVCenter, timeStr);

}
