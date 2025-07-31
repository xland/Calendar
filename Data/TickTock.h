#pragma once
#include <QApplication>
#include <QTimer>
#include <QObject>

class ScheduleModel;
class TickTock  : public QObject
{
	Q_OBJECT

public:
	TickTock(QObject *parent);
	~TickTock();
	void start();
	static void init();
	static TickTock* get();
private:
	void timeout();
	QTimer* timer;
};

