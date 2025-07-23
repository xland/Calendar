#pragma once

#include <QObject>

class Eventer  : public QObject
{
	Q_OBJECT

public:
	Eventer(QObject *parent);
	~Eventer();
	static void init();
	static Eventer* get();
signals:
	void schedulesChange();
};

