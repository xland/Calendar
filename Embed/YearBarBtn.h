#pragma once
#include <QMouseEvent>
#include <QWidget>

#include "BtnBase.h"
class YearBarBtn : public BtnBase
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
