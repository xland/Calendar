#pragma once

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include "../Data/ScheduleModel.h"

class Alert : public QWidget
{
	Q_OBJECT

public:
	Alert(const QString& modelId, QWidget *parent = nullptr);
	~Alert();
protected:
private:
	void okBtnClick();
	void timeout();
private: 
	ScheduleModel* model;
	QLabel* remainTimeText;
	QTimer* timer;
};

