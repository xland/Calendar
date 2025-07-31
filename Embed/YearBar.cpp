#include <QRect>
#include <QPainter>
#include <QHBoxLayout>

#include "Util.h"
#include "YearBar.h"
#include "DayBtn.h"
#include "../Data/Dates.h"
#include "../Data/DateModel.h"


YearBar::YearBar(QWidget *parent) : QWidget(parent)
{
	setGeometry(0, 0, 372, 40);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(22, 0, 18, 0);
	yearMonthLabel = new QLabel(this);
	layout->addWidget(yearMonthLabel);
	setYearMonthText(QDate::currentDate());
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
	connect(Dates::get(), &Dates::datesChanged, this, [this]() {setYearMonthText(Dates::get()->dates[21]->date); });
}

YearBar::~YearBar()
{
}

void YearBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setFont(Util::getTextFont(20));
	painter.setPen(QColor(31, 35, 41));
	painter.drawText(rect(), Qt::AlignCenter, activeDateMonth);
}


void YearBar::leftBtnClick()
{
	auto date = Dates::get()->dates[21];
	Dates::get()->initOneMonthDate(date->date.addMonths(-1));
}

void YearBar::rightBtnClick()
{
	auto date = Dates::get()->dates[21];
	Dates::get()->initOneMonthDate(date->date.addMonths(1));
}

void YearBar::todayBtnClick()
{
	Dates::get()->initOneMonthDate(QDate::currentDate());
}

void YearBar::setYearMonthText(const QDate& date)
{
	auto text = QString("%1年%2月").arg(date.year()).arg(date.month());
	yearMonthLabel->setText(text);
}
