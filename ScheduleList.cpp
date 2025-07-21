#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include "ScheduleList.h"
#include "ScheduleListItem.h"
#include "Eventer.h"

ScheduleList::ScheduleList(QWidget *parent) : QScrollArea(parent)
{
    setFrameShape(QFrame::NoFrame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(R"(QScrollArea{border: none; background: #ffffff;}
QScrollBar:vertical{border: none; background: transparent; /* 滚动条背景颜色 */
    width: 6px;/* 滚动条宽度 */ margin: 0px 0px 0px 0px;}
QScrollBar::handle:vertical { background: #dddddd; /* 滑块颜色 */
    min-height: 20px;/* 滑块最小高度 */ border-radius: 0px;  /* 圆角 */}
QScrollBar::handle:vertical:hover { background: #cccccc; /* 鼠标悬停时的滑块颜色 */ }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; /* 移除上下箭头 */ background: none; }
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; /* 滑块上下区域的背景 */ })");


    auto contentWidget = new QWidget(this);
    contentWidget->setStyleSheet("background: #ffffff;");
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);
    //auto item = new QLabel("测试测试测试");
    //contentLayout->addWidget(item);
    setWidget(contentWidget);
    setWidgetResizable(true);
    refreshData();

    QObject::connect(Eventer::get(), &Eventer::globalEvent, this,&ScheduleList::refreshData);
}

ScheduleList::~ScheduleList()
{}

void ScheduleList::refreshData()
{
    QLayoutItem* child;
    while ((child = contentLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM Job");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return;
    }

    while (query.next()) {
        auto m = new ScheduleModel(query,this);
        auto item = new ScheduleListItem(m);
        connect(item, &ScheduleListItem::click, this, &ScheduleList::itemClick);
        contentLayout->addWidget(item);
    }
    contentLayout->addStretch();
    contentLayout->update();
    contentLayout->activate();
}

void ScheduleList::itemClick()
{
    auto tar = sender();
    for (int i = 0; i < contentLayout->count(); ++i) {
        QLayoutItem* childItem = contentLayout->itemAt(i);
        if (!childItem) continue; 
         auto item = qobject_cast<ScheduleListItem*>(childItem->widget());
         if (!item) continue;
         if (item != sender()) {
             if (item->isSelected != false) {
                 item->isSelected = false;
                 item->update();
             }
         }
    }
}

