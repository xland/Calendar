#pragma once
#include <QMouseEvent>
#include <QWidget>
#include <QDate>
#include "BtnBase.h"

class DayBtn : public BtnBase
{
	Q_OBJECT
public:
	DayBtn(const int& index,QWidget *parent = nullptr);
	~DayBtn();
public:
	int index;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void onClick();
private:

};
