#include <QRect>
#include <QPainter>

#include "Menu.h"
#include "MainWindow.h"
#include "TipInfo.h"
#include "Util.h"
#include "Skin.h"
#include "YearBar.h"
#include "Toast.h"

YearBar* yearBar;


YearBar::YearBar(QWidget *parent) : QWidget(parent)
{
	setGeometry(0, 0, 372, 44);
	leftBtn = new YearBarBtn(0xe60e,this);
	leftBtn->move(204, 12);
	rightBtn = new YearBarBtn(0xe638,this);
	rightBtn->move(252, 12);
	todayBtn = new YearBarBtnToday(this);
	todayBtn->move(320, 12);
	//connect(leftBtn, &YearBarBtn::enter, this, &YearBar::leftBtnEnter);
	//connect(rightBtn, &YearBarBtn::enter, this, &YearBar::rightBtnEnter);

	connect(leftBtn, &YearBarBtn::click, this, &YearBar::leftBtnClick);
	connect(rightBtn, &YearBarBtn::click, this, &YearBar::rightBtnClick);
	connect(todayBtn, &YearBarBtn::click, this, &YearBar::todayBtnClick);

	//connect(leftBtn, &YearBarBtn::leave, this, &YearBar::btnLeave);
	//connect(rightBtn, &YearBarBtn::leave, this, &YearBar::btnLeave);
	//connect(todayBtn, &YearBarBtn::leave, this, &YearBar::btnLeave);
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
	yearBar->leftTip = "上月";
	yearBar->rightTip = "下月";
	yearBar->activeDateMonth =  "";
	yearBar->todayBtn->isCn = true;
	yearBar->show();
}

void YearBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	auto font = Util::getTextFont(20);
	painter.setFont(*font);
	auto skin = Skin::get();
	painter.setPen(skin->year);
	painter.drawText(rect(), Qt::AlignCenter, activeDateMonth);
}

void YearBar::leftBtnEnter()
{
	auto tipObj = TipInfo::get();
	tipObj->setText(leftTip);
	tipObj->showInfo(QPoint(78, 26));
}

void YearBar::rightBtnEnter()
{
	if (Menu::get()->isVisible()) return;
	auto tipObj = TipInfo::get();
	tipObj->setText(rightTip);
	tipObj->showInfo(QPoint(238, 26));
}

void YearBar::leftBtnClick()
{

}

void YearBar::rightBtnClick()
{
}

void YearBar::todayBtnClick()
{

}

void YearBar::btnLeave()
{
	TipInfo::get()->hide();
}
