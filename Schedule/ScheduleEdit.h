#pragma once
#include <QPlainTextEdit>
#include <QDateTimeEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "../Data/ScheduleModel.h"
#include "RepeatSelection.h"

class ScheduleEdit : public QWidget
{
	Q_OBJECT

public:
	ScheduleEdit(QWidget *parent = nullptr);
	~ScheduleEdit();
	void updateData();

private:
	void save();
	void initDateEdit(QVBoxLayout* layout);
	void initTextEdit(QVBoxLayout* layout);
	void initBtns(QVBoxLayout* layout);
	QPlainTextEdit* plainTextEdit;
	QDateTimeEdit* dateTimeEdit;
	RepeatSelection* repeatSelection;
	ScheduleModel* data;
	QPushButton* btn;
};

