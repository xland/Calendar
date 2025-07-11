#pragma once
#include <QMouseEvent>
#include <QWidget>

#include "YearBarBtnBase.h"
class YearBarBtn : public YearBarBtnBase
{
	Q_OBJECT
public:
	YearBarBtn(const uint& code, QWidget *parent = nullptr);
	~YearBarBtn();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	uint code;
};
