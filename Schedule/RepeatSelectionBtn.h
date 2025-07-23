#pragma once
#include <QPainter>
#include "../BtnBase.h"

class RepeatSelectionBtn : public BtnBase
{
	Q_OBJECT

public:
	RepeatSelectionBtn(const int& val, QWidget *parent = nullptr);
	~RepeatSelectionBtn();
	QString labelStr;
	int val;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};

