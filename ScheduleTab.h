#pragma once

#include <QWidget>
#include <QPainter>

#include "BtnBase.h"

class ScheduleTab : public BtnBase
{
	Q_OBJECT

public:
	ScheduleTab(QWidget *parent = nullptr);
	~ScheduleTab();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};

