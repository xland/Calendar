#pragma once
#include <QDate>
#include <QObject>

class DateModel  : public QObject
{
	Q_OBJECT
public:
	DateModel(QObject *parent);
	~DateModel();
	QDate date;
	QString lunar;
	bool hasSchedule{false};
	bool isToday;
	bool isCurMonth;
};

