#pragma once

#include <QWidget>
#include <QPainter>
#include "../BtnBase.h"

class ScheduleModel;
class UpcomingItem : public BtnBase
{
	Q_OBJECT

public:
	UpcomingItem(const int& i, ScheduleModel* model,QWidget *parent = nullptr);
	~UpcomingItem();
	void updateTime();
	void itemClick();
	QString timeStr;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	int index;
	ScheduleModel* model;
};

