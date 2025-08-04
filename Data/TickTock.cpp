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
	auto data = Schedules::get()->getRecentData(1);
	if (data.count() <= 0) return;
	auto now = QDateTime::currentDateTime().toSecsSinceEpoch();
	auto tickCount = data[0]->UpcomingTime - now - SettingModel::get()->AlertBefore*60; //提前5分钟
	if (tickCount < 0) tickCount = 0;
	QVariant var;
	var.setValue(data[0]);
	timer->setProperty("data", var);
	timer->start(tickCount * 1000); //此处不能为负值，如果是负值的话，将不会马上触发回调事件
}
void TickTock::reset() {
	tickTock->timer->stop();
	auto item = tickTock->timer->property("data").value<ScheduleModel*>();
	if (item) {
		item->deleteLater();
	}	
	tickTock->start();
}
void TickTock::timeout()
{
	auto item = timer->property("data").value<ScheduleModel*>();
	if (item) {
		item->IsExpire = true;
		item->update();
		auto alert = new Alert(item->Id);
		alert->show();
		item->deleteLater();
		QVariant var;
		var.setValue(nullptr);
		timer->setProperty("data", var);
	}
	start();
}

