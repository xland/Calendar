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
	void delData(const QString& id);
	void editData(ScheduleModel* data);
	void addData(ScheduleModel* data);
	ScheduleModel* getData(const QString& id);
	bool hasSchedule(const QDate& day, const QList<ScheduleModel*>& data);
	QList<ScheduleModel*> getData(const QDate& startD, const QDate& endD, const QString& keyword="");
	QList<ScheduleModel*> getDataAll();
	ScheduleModel* getRecentData(const QList<ScheduleModel*>& data);

private:


};

