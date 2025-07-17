#pragma once

#include <QWidget>

class ScheduleEdit : public QWidget
{
	Q_OBJECT

public:
	ScheduleEdit(QWidget *parent = nullptr);
	~ScheduleEdit();

private:
	void save();
};

