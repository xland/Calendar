#pragma once
#include <QSqlQuery>
#include <QObject>

class ScheduleModel  : public QObject
{
	Q_OBJECT

public:
	ScheduleModel(const QSqlQuery& query,QObject *parent);
	~ScheduleModel();
	QString Id;
	QString JobInfo;
	long long StartTime;
	int RepeatType;
};

