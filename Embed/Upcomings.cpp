#include <QVBoxLayout>

#include "Upcomings.h"
#include "UpcomingItem.h"
#include "../Data/SettingModel.h"
#include "../Data/Schedules.h"
#include "../Data/SettingModel.h"
#include "MainWindow.h"

Upcomings::Upcomings(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 0, 12, 0);
    layout->setSpacing(0);
    move(0,316);
    setLayout(layout);
    //数量改变时，更新
    auto num = SettingModel::get()->UpcomingNum;
    if (num > 0) {
        initChildren();
    }
    else {
        parent->setFixedSize(QSize(370, 328));
        setFixedSize(370,0);
    }
    connect(SettingModel::get(), &SettingModel::settingChanged, this, &Upcomings::needChange);
    connect(Schedules::get(), &Schedules::scheduleChanged, this, &Upcomings::needChange);
}

Upcomings::~Upcomings()
{

}

void Upcomings::timeout() {
    bool refreshFlag{ false };
    for (size_t i = 0; i < upcomingItems.size(); i++)
    {
        upcomingItems[i]->updateTime();
        if (upcomingItems[i]->timeStr == "已发生") {
            refreshFlag = true;
            break;
        }
    }
    if (refreshFlag) {
        needChange();
    }
}

void Upcomings::needChange() {
    removeTimer();
    auto l = layout();
    QLayoutItem* item;
    while ((item = l->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            delete widget; 
        }
        delete item; 
    }
    upcomingItems.clear();
    initChildren();
}

void Upcomings::removeTimer()
{
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}

void Upcomings::initChildren()
{
    auto data = Schedules::get()->getUpcomingData(SettingModel::get()->UpcomingNum);
    auto h = data.size() * 28;
    auto win = (MainWindow*)parent();
    win->setFixedSize(QSize(370, 328 + h));
    setFixedSize(370, h);
    if (data.size() > 0) {
        for (int i = 0; i < data.size(); i++)
        {
            auto item = new UpcomingItem(i, data[i]);
            layout()->addWidget(item);
            upcomingItems.append(item);
        }
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Upcomings::timeout);
        timer->start(1000);
    }
    else {
        removeTimer();
    }
}
