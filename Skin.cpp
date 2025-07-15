#include <QCoreApplication>
#include <QJsonObject>
#include "Skin.h"


namespace {
	Skin* skin;
}

Skin::Skin(QObject* parent) : QObject(parent)
{

}

Skin::~Skin()
{
}

void Skin::init()
{
	if (!skin) {
		skin = new Skin(qApp);
	}
	auto theme = "type1";
	auto alpha = 0.6;
	auto alphaVal = static_cast<int>(std::round(alpha * 255));
	skin->dayActive.setRgb(240, 44, 56);
	skin->switchText.setRgb(0, 122, 255);
	skin->dayWorking.setRgb(0, 122, 255);
	skin->listItemBg.setRgb(255, 255, 255, 51);
	skin->yearBtnTodayBorder.setRgb(240, 44, 56, 255);
	skin->yearBtnToday.setRgb(240, 44, 56, 255);
	if (theme == "type1") {
		skin->bg.setRgb(255, 255, 255, alphaVal);
		skin->initWhite();
	}
	else {
		skin->bg.setRgb(0, 0, 0, alphaVal);
		skin->initBlack();
	}
}

Skin* Skin::get()
{
	return skin;
}

void Skin::initBlack()
{
	titleBtn.setRgb(210, 211, 212);
	titleBtnHover.setRgb(255, 255, 255, 51);

	menuBg.setRgb(0, 0, 0);
	menuHover.setRgb(255, 255, 255, 51);
	menu.setRgb(255, 255, 255);

	year.setRgb(255, 255, 255);
	yearBtnHover.setRgb(255, 255, 255, 64);
	yearBtnBorder.setRgb(237, 238, 238);
	yearBtn.setRgb(255, 255, 255);

	yearBtnTodayHover.setRgb(255, 255, 255, 64);

	week.setRgb(210, 211, 212);
	day.setRgb(255, 255, 255);
	lunar.setRgb(210, 211, 212);
	dayNotCurMonth.setRgb(165, 167, 169);
	lunarNotCurMonth.setRgb(165, 167, 169);
	dot.setRgb(165, 167, 169);
	dayHover.setRgb(255, 255, 255, 90);

	listHeader.setRgb(255, 255, 255);
	listItemText1.setRgb(255, 255, 255);
	listItemText2.setRgb(165, 167, 169);
	listItemBtn.setRgb(210, 211, 212);

	tipInfoBg.setRgb(255, 255, 255);
	tipInfo.setRgb(31, 35, 41);
}

void Skin::initWhite()
{
	titleBtn.setRgb(100, 106, 115);
	titleBtnHover.setRgb(0, 0, 0, 38);

	menuBg.setRgb(237, 238, 238);
	menuHover.setRgb(224, 224, 224);
	menu.setRgb(31, 35, 41);

	year.setRgb(31, 35, 41);
	yearBtnHover.setRgb(255, 255, 255, 76);
	yearBtnBorder.setRgb(121, 123, 127);
	yearBtn.setRgb(76, 79, 84);

	yearBtnTodayHover.setRgb(240, 44, 56, 51);

	week.setRgb(120, 120, 120);
	day.setRgb(31, 35, 41);
	lunar.setRgb(76, 79, 84);
	dayNotCurMonth.setRgb(102, 102, 102);
	lunarNotCurMonth.setRgb(102, 102, 102);
	dot.setRgb(102, 102, 102);
	dayHover.setRgb(255, 255, 255, 128);

	listHeader.setRgb(31, 35, 41);
	listItemText1.setRgb(31, 35, 41);
	listItemText2.setRgb(102, 102, 102);
	listItemBtn.setRgb(76, 79, 84);

	tipInfoBg.setRgb(26, 26, 26);
	tipInfo.setRgb(255, 255, 255);
}