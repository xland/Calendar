#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include "RepeatSelection.h"
#include "../Data/ScheduleModel.h"

class DialogEdit : public QWidget
{
	Q_OBJECT

public:
	DialogEdit(const QString& id, const QDate& date, QWidget *parent = nullptr);
	~DialogEdit();
protected:
	void showEvent(QShowEvent* event) override;
private:
	void initDateEdit(QVBoxLayout* layout);
	void initTextEdit(QVBoxLayout* layout);
	void initBtns(QVBoxLayout* layout);
	void initData(const QString& id);
	void btnClick();
	QString title;
	QPlainTextEdit* plainTextEdit;
	QDateTimeEdit* dateTimeEdit;
	RepeatSelection* repeatSelection;
	QPushButton* btn;
	ScheduleModel* data;
	QDate date;
};

