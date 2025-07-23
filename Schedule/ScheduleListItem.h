#pragma once
#include <QPainter>
#include <QWidget>
#include "../Data/ScheduleModel.h"
class ScheduleListItem : public QWidget
{
	Q_OBJECT

public:
	ScheduleListItem(ScheduleModel* model, QWidget *parent = nullptr);
	~ScheduleListItem();
	bool isSelected{ false };
	ScheduleModel* model{ nullptr };
protected:
	void paintEvent(QPaintEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
signals:
	void click();
private:
	bool isHover{ false };
};

