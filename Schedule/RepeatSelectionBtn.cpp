﻿#include "RepeatSelectionBtn.h"
#include "Util.h"
#include "RepeatSelection.h"

RepeatSelectionBtn::RepeatSelectionBtn(const int& val, QWidget* parent) : BtnBase(parent), val{val}
{ 
	if (val == 1) {
		setFixedWidth(66);
		labelStr = "不重复";
	}
	else if (val == 2) {
		setFixedWidth(52);
		labelStr = "每天";
	}
	else if (val == 3) {
		setFixedWidth(90);
		labelStr = "每个工作日";
	}
	else if (val == 4) {
		setFixedWidth(66);
	}
	else if (val == 5) {
		setFixedWidth(90);
	}
	else if (val == 6) {
		setFixedWidth(100);
	}
}

RepeatSelectionBtn::~RepeatSelectionBtn()
{

}

void RepeatSelectionBtn::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	auto p = (RepeatSelection*)parent();
	painter.setFont(Util::getIconFont(12));
	painter.setPen(QColor(60, 80, 130));
	if (val == p->selectedVal) {
		painter.drawText(0, 12, QChar(0xe72d));
	}
	else if(!isHover) {
		painter.setPen(QColor(100, 100, 100));
	}
	painter.drawText(0, 12, QChar(0xe6b6));
	painter.setFont(Util::getTextFont(13));
	painter.drawText(16, 12, labelStr);
}

