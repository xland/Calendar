#pragma once
#include <QDate>
#include <QDateTime>
#include <QObject>

class DateModel;
class Dates  : public QObject
{
	Q_OBJECT

public:
	Dates(QObject *parent);
	~Dates();
	static void init();
	static Dates* get();
	static void refresh();
	void initOneMonthDate(const QDate& tarDate);
signals:
	void datesChanged();
public:
	QList<DateModel*> dates;
};

