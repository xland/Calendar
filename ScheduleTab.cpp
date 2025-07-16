#include <QHBoxLayout>
#include <QPushButton>
#include "ScheduleTab.h"
#include "Util.h"

ScheduleTab::ScheduleTab(QWidget *parent) : BtnBase(parent)
{
    setFixedHeight(28);

    //auto btnLayout = new QHBoxLayout(this);
    //btnLayout->setContentsMargins(0, 0, 0, 0);
    //btnLayout->setSpacing(0);
    //QPushButton* button = new QPushButton("当日日程");
    //button->setFixedWidth(80);
    //btnLayout->addWidget(button);
    //QPushButton* clearButton = new QPushButton("全部日程");
    //clearButton->setFixedWidth(80);
    //btnLayout->addWidget(clearButton);
    //btnLayout->addStretch();
}

ScheduleTab::~ScheduleTab()
{
	
}

void ScheduleTab::paintEvent(QPaintEvent* event)
{
    int rw = 80;
    QRect curRect(0, 0, rw, 28);
    QRect allRect(rw, 0, rw, 28);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QColor(255, 255, 255));
    painter.setPen(Qt::NoPen);
    painter.drawRect(curRect);

    painter.setFont(Util::getTextFont(12));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(30,30,30));
    painter.drawText(curRect, Qt::AlignCenter, "当日日程");
    painter.setPen(QColor(100, 100, 100));
    painter.drawText(allRect, Qt::AlignCenter, "全部日程");
}

