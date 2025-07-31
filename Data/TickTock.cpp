#include <QMessageBox>

#include "TickTock.h"
#include "ScheduleModel.h"
#include "Schedules.h"

TickTock* tickTock;

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
	timer->start(1 * 1000);
}

void TickTock::timeout()
{
	QMessageBox::information(nullptr, "标题", "这是一条信息内容");
}

