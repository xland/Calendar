#pragma once
#include <QObject>
#include <QSqlQuery>
class ScheduleModel  : public QObject
{
	Q_OBJECT

public:
	ScheduleModel(QObject* parent = nullptr);
	ScheduleModel(QSqlQuery& query,QObject* parent = nullptr);
	ScheduleModel(const QString& id, QObject* parent = nullptr);
	~ScheduleModel();
	void insert();
	void update();
	void del();
	static void del(const QString& id);
	void setUpcomingTime();
	void setNextTime();
public:
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
private:
	void initByQuery(QSqlQuery& query);
};

