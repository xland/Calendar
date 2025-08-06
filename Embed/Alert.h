#pragma once

#include <QDialog>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include "../Data/ScheduleModel.h"

class Alert : public QDialog
{
	Q_OBJECT

public:
	Alert(const QString& modelId, QWidget *parent = nullptr);
	~Alert();
protected:
private:
	void okBtnClick();
	void timeout();
	void modelChange();
	void removeTimer();
private: 
	ScheduleModel* model;
	QLabel* remainTimeText;
	QTimer* timer;
	QString Id;
};

