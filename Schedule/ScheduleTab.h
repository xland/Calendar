#pragma once

#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

#include "../BtnBase.h"

class ScheduleTab : public QWidget
{
	Q_OBJECT

public:
	ScheduleTab(QWidget *parent = nullptr);
	~ScheduleTab();
	bool isCurDayTab{ true };
protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
private:
	void addNew();
	int rw{ 80 };
	int hoverIndex{ -1 };
};

