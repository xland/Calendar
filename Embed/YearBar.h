#pragma once
#include <QMouseEvent>
#include <QWidget>
#include <QLabel>
#include "YearBarBtn.h"

class YearBar : public QWidget
{
	Q_OBJECT
public:
	YearBar(QWidget* parent = nullptr);
	~YearBar();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void leftBtnClick();
	void rightBtnClick();
	void todayBtnClick();
	void setYearMonthText(const QDate& date);
private:
	YearBarBtn* leftBtn;
	YearBarBtn* rightBtn;
	YearBarBtn* todayBtn;
	YearBarBtn* settingBtn;
	QString activeDateMonth;
	QLabel* yearMonthLabel;
};
