#pragma once
#include <QDate>
#include <QWidget>

class DialogSchedule : public QWidget
{
	Q_OBJECT

public:
	DialogSchedule(const QDate& day, QWidget *parent = nullptr);
	~DialogSchedule();
	QDate curDay;
private:
};

