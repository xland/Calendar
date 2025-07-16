#include <QRect>
#include <QPainter>
#include <QHBoxLayout>

#include "Menu.h"
#include "MainWindow.h"
#include "TipInfo.h"
#include "Util.h"
#include "Skin.h"
#include "YearBar.h"
#include "Toast.h"
#include "DayBtn.h"

YearBar* yearBar;


YearBar::YearBar(QWidget *parent) : QWidget(parent)
{
	setGeometry(0, 0, 372, 40);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(22, 0, 18, 0);
	yearMonthLabel = new QLabel(this);
	layout->addWidget(yearMonthLabel);
	layout->addStretch();

	leftBtn = new YearBarBtn(0xe60e, this);
	rightBtn = new YearBarBtn(0xe638, this);
	todayBtn = new YearBarBtn(0xe667, this);
	settingBtn = new YearBarBtn(0xe643, this);
	layout->addWidget(leftBtn);
	layout->addWidget(rightBtn);
	layout->addWidget(todayBtn);
	layout->addWidget(settingBtn);
	setLayout(layout);

	connect(leftBtn, &YearBarBtn::click, this, &YearBar::leftBtnClick);
	connect(rightBtn, &YearBarBtn::click, this, &YearBar::rightBtnClick);
	connect(todayBtn, &YearBarBtn::click, this, &YearBar::todayBtnClick);
}

YearBar::~YearBar()
{
	yearBar = nullptr;
}

void YearBar::init()
{
	if (!yearBar) {
		yearBar = new YearBar(MainWindow::get());
	}
	yearBar->activeDateMonth =  "";
	yearBar->show();
}

YearBar* YearBar::get() {
	return yearBar;
}

void YearBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setFont(Util::getTextFont(20));
	auto skin = Skin::get();
	painter.setPen(skin->year);
	painter.drawText(rect(), Qt::AlignCenter, activeDateMonth);
}


void YearBar::leftBtnClick()
{
	switchMonth(-1);
}

void YearBar::rightBtnClick()
{
	switchMonth(1);
}

void YearBar::todayBtnClick()
{
	auto win = (MainWindow*)parent();
	win->updateData(QDate::currentDate());
}

void YearBar::switchMonth(const int& val)
{
	auto win = (MainWindow*)parent();
	QDate day;
	for (auto& btn : win->dayBtns)
	{
		if (btn->isCurMonth) {
			day = btn->day.addMonths(val);
			break;
		}
	}
	win->updateData(day);
}
