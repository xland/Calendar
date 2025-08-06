#include <QMessageBox>
#include <QDateTime>

#include "TickTock.h"
#include "ScheduleModel.h"
#include "Schedules.h"
#include "../Data/SettingModel.h"
#include "../Embed/Alert.h"

static TickTock* tickTock;

TickTock::TickTock(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &TickTock::timeout);
	connect(Schedules::get(), &Schedules::scheduleChanged, this, &TickTock::reset);
	connect(SettingModel::get(), &SettingModel::settingChanged, this, &TickTock::reset);
}

TickTock::~TickTock()
{

}

void TickTock::init()
{
	if (!tickTock) {
		tickTock = new TickTock(qApp);
	}
}

TickTock* TickTock::get()
{
	return tickTock;
}

void TickTock::start() {
	QList<ScheduleModel*> data;
	if (model) {
		data = Schedules::get()->getUpcomingData(1, model->UpcomingTime);
		delete model;
		model = nullptr;
	}
	else {
		data = Schedules::get()->getUpcomingData(1);
	}
	if (data.count() <= 0) return;
	auto now = QDateTime::currentDateTime().toSecsSinceEpoch();
	auto tickCount = data[0]->UpcomingTime - now - SettingModel::get()->AlertBefore*60; //提前5分钟
	if (tickCount < 0) tickCount = 0;
	model = data[0];
	timer->start(tickCount * 1000); //此处不能为负值，如果是负值的话，将不会马上触发回调事件
}
void TickTock::reset() {
	tickTock->timer->stop();
	if (model) {
		delete model;
		model = nullptr;
	}	
	tickTock->start();
}
void TickTock::timeout()
{
	if (model) {
		auto alert = new Alert(model->Id);
		alert->show();
	}
	start();
}

