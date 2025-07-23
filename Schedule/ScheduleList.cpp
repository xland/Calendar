#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

#include "ScheduleList.h"
#include "ScheduleListItem.h"
#include "Eventer.h"
#include "../Data/Schedules.h"

ScheduleList::ScheduleList(QWidget *parent) : QScrollArea(parent)
{
    setFrameShape(QFrame::NoFrame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("QScrollArea{border:none;background:#ffffff;}"
        "QScrollBar:vertical{border:none; background:transparent;width:6px;margin:0px 0px 0px 0px;}" /* 滚动条背景颜色与宽度 */
        "QScrollBar::handle:vertical{background:#dddddd;min-height:20px;border-radius:0px;}" /* 滑块颜色 滑块最小高度 */
        "QScrollBar::handle:vertical:hover{background:#cccccc;}" /* 鼠标悬停时的滑块颜色 */
        "QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0px;background:none;}"/* 移除上下箭头 */ 
        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:none;})"); /* 滑块上下区域的背景 */
    auto contentWidget = new QWidget(this);
    contentWidget->setStyleSheet("background:#ffffff;");
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout = new QVBoxLayout(contentWidget);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setWidget(contentWidget);
    setWidgetResizable(true);
    QObject::connect(Eventer::get(), &Eventer::schedulesChange, this,&ScheduleList::refreshData);
    refreshData();
}

ScheduleList::~ScheduleList()
{}

void ScheduleList::refreshData()
{
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    auto& list = Schedules::get()->data;
    for (size_t i = 0; i < list.size(); i++)
    {
        auto item = new ScheduleListItem(list[i]);
        connect(item, &ScheduleListItem::click, this, &ScheduleList::itemClick);
        layout->addWidget(item);
    }
    layout->addStretch();
    layout->update();
    layout->activate();
}

void ScheduleList::itemClick()
{
    auto tar = sender();
    for (int i = 0; i < layout->count(); ++i) {
        QLayoutItem* childItem = layout->itemAt(i);
        if (!childItem) continue; 
         auto item = qobject_cast<ScheduleListItem*>(childItem->widget());
         if (!item) continue;
         if (item != sender()) {
             if (item->model->isSelected != false) {
                 item->model->isSelected = false;
                 item->update();
             }
         }
    }
}

