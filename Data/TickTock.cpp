#include "TickTock.h"

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

}
void TickTock::timeout()
{
}

