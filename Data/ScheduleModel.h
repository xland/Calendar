#pragma once
#include <QObject>
#include <QSqlQuery>
class ScheduleModel  : public QObject
{
	Q_OBJECT

public:
	ScheduleModel(QObject* parent);
	ScheduleModel(QSqlQuery& query,QObject* parent);
	~ScheduleModel();
	QString Id;
	QString Schedule;
	int RepeatType{1};
	qint64 CreateTime;
	qint64 FirstTime;
	qint64 UpcomingTime;
	bool IsExpire{ false };
	int Year;
	int Month;
	int Day;
	int Time;
};

