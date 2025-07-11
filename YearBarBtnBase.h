#pragma once
#include <QMouseEvent>
#include <QWidget>
#include <QColor>

#include "BtnBase.h"

class YearBarBtnBase : public BtnBase
{
	Q_OBJECT
public:
	YearBarBtnBase(QWidget *parent = nullptr);
	~YearBarBtnBase();
protected:
	virtual void paintEvent(QPaintEvent* event) override;
protected:
};
