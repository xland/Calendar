#include <QApplication>
#include "Eventer.h"

Eventer* eventer{nullptr};

Eventer::Eventer(QObject *parent) : QObject(parent)
{}

Eventer::~Eventer()
{}

void Eventer::init() 
{
	if (!eventer) {
		eventer = new Eventer(qApp);
	}
	
}
Eventer* Eventer::get() 
{
	return eventer;
}

void Eventer::fire(const QString& eventName, const QObject* data)
{
	eventer->emit globalEvent(eventName, data);
}
