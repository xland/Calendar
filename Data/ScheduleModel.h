#pragma once
#include <QSqlQuery>
#include <QObject>

class ScheduleModel  : public QObject
{
	Q_OBJECT

public:
	ScheduleModel(QObject* parent);
	ScheduleModel(const QString& JobInfo,const long long& StartTime,const int& RepeatType, QObject* parent);
	~ScheduleModel();
	QString Id;
	QString JobInfo;
	long long StartTime;
	int RepeatType;

	bool isSelected{ false };
};

