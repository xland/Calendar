#pragma once
#include <QMouseEvent>
#include <QWidget>
#include "YearBarBtnBase.h"
class YearBarBtnToday : public YearBarBtnBase
{
	Q_OBJECT
public:
	YearBarBtnToday(QWidget *parent = nullptr);
	~YearBarBtnToday();
	bool isCn;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};
