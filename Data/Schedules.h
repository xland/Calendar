#pragma once

#include <QObject>


#include "ScheduleModel.h"

class Schedules  : public QObject
{
	Q_OBJECT

public:
	Schedules(QObject *parent);
	~Schedules();
	static void init();
	static Schedules* get();
	bool hasSchedule(const QDate& date);
	QList<ScheduleModel*> getData(const QDate& startD, const QDate& endD, const QString& keyword="");
	QList<ScheduleModel*> getUpcomingData(const int& count);
	QList<ScheduleModel*> getUpcomingData(const int& count,qint64 time);
signals:
	void scheduleChanged();
private:
	void updateUpcomingSchedule();
};

