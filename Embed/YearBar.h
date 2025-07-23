#pragma once
#include <QMouseEvent>
#include <QWidget>
#include <QLabel>
#include "YearBarBtn.h"

class YearBar : public QWidget
{
	Q_OBJECT
public:
	~YearBar();
	static void init();
	static YearBar* get();
	QLabel* yearMonthLabel;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void leftBtnClick();
	void rightBtnClick();
	void todayBtnClick();
	void switchMonth(const int& val);
private:
	YearBar(QWidget* parent = nullptr);
	YearBarBtn* leftBtn;
	YearBarBtn* rightBtn;
	YearBarBtn* todayBtn;
	YearBarBtn* settingBtn;
	QString activeDateMonth;
};
