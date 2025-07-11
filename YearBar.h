#pragma once
#include <QMouseEvent>
#include <QWidget>
#include "YearBarBtn.h"
#include "YearBarBtnToday.h"

class YearBar : public QWidget
{
	Q_OBJECT
public:
	~YearBar();
	static void init();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void leftBtnEnter();
	void rightBtnEnter();
	void leftBtnClick();
	void rightBtnClick();
	void todayBtnClick();
	void btnLeave();
private:
	YearBar(QWidget* parent = nullptr);
	YearBarBtn* leftBtn;
	YearBarBtn* rightBtn;
	YearBarBtnToday* todayBtn;
	QString leftTip;
	QString rightTip;
	QString activeDateMonth;
};
