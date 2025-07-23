#pragma once
#include <QVBoxLayout>
#include <QScrollArea>

class ScheduleList : public QScrollArea
{
	Q_OBJECT

public:
	ScheduleList(QWidget *parent = nullptr);
	~ScheduleList();
	void refreshData();
private:
	void itemClick();
	QVBoxLayout* layout;
};

