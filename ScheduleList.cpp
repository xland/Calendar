#include <QVBoxLayout>
#include <QLabel>
#include "ScheduleList.h"

ScheduleList::ScheduleList(QWidget *parent) : QScrollArea(parent)
{
    setFrameShape(QFrame::NoFrame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(R"(QScrollArea{border: none; background: #ffffff;}
QScrollBar:vertical{border: none; background: transparent; /* 滚动条背景颜色 */
    width: 6px;/* 滚动条宽度 */ margin: 0px 0px 0px 0px;}
QScrollBar::handle:vertical { background: #dddddd; /* 滑块颜色 */
    min-height: 20px;/* 滑块最小高度 */ border-radius: 2px;  /* 圆角 */}
QScrollBar::handle:vertical:hover { background: #cccccc; /* 鼠标悬停时的滑块颜色 */ }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; /* 移除上下箭头 */ background: none; }
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; /* 滑块上下区域的背景 */ })");


    auto contentWidget = new QWidget(this);
    contentWidget->setFixedWidth(parent->width());
    //contentWidget->setStyleSheet(R"(background:#99aadd;)");
    auto contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    /*auto item = new QLabel("测试测试测试");
    contentLayout->addWidget(item);*/
    setWidget(contentWidget);
}

ScheduleList::~ScheduleList()
{}

