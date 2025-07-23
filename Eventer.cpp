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
