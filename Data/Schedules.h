#pragma once

#include <QObject>

#include "ScheduleModel.h"

class Schedules  : public QObject
{
	Q_OBJECT

public:
	Schedules(QObject *parent);
	~Schedules();
	void delData(const QString& id);
	void editData(ScheduleModel* data);
	void addData(ScheduleModel* data);
	ScheduleModel* getData(const QString& id);
	bool hasSchedule(const QDate& day);
	QList<ScheduleModel*> getData(const QDate& startD, const QDate& endD);
	QList<ScheduleModel*> getDataAll();
	static void init();
	static Schedules* get();
	QList<ScheduleModel*> data;
private:
	void initData();
};

