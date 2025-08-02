#pragma once
#include <QMouseEvent>
#include <QWidget>
#include <QLabel>
#include "YearBarBtn.h"

class BtnBase;
class YearBar : public BtnBase
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
	void settingBtnClick();
	void setYearMonthText(const QDate& date);
	void mousePressEvent(QMouseEvent* event) override;
private:
	YearBarBtn* leftBtn;
	YearBarBtn* rightBtn;
	YearBarBtn* todayBtn;
	YearBarBtn* settingBtn;
	QString activeDateMonth;
	QLabel* yearMonthLabel;
};
