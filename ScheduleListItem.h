#pragma once
#include <QPainter>
#include <QWidget>
#include "ScheduleModel.h"
class ScheduleListItem : public QWidget
{
	Q_OBJECT

public:
	ScheduleListItem(ScheduleModel* model, QWidget *parent = nullptr);
	~ScheduleListItem();
	bool isSelected{ false };
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
signals:
	void click();
private:
	ScheduleModel* model{ nullptr };
	bool isHover{ false };
};

