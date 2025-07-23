#pragma once

#include <QObject>

#include "ScheduleModel.h"

class Schedules  : public QObject
{
	Q_OBJECT

public:
	Schedules(QObject *parent);
	~Schedules();
	void addData(const QString& JobInfo, const long long& StartTime, const int& RepeatType);
	static void init();
	static Schedules* get();
	QList<ScheduleModel*> data;
private:
	void initData();
};

