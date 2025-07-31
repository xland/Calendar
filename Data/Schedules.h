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
	void setUpcomingTime(ScheduleModel* data);
	void delData(const QString& id);
	void editData(ScheduleModel* data);
	void addData(ScheduleModel* data);

	ScheduleModel* getData(const QString& id);
	bool hasSchedule(const QDate& date);
	QList<ScheduleModel*> getData(const QDate& startD, const QDate& endD, const QString& keyword="");
signals:
	void scheduleChanged();
private:
	void updateUpcomingSchedule();
};

