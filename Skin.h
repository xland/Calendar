#pragma once
#include <QColor>
class Skin : public QObject
{
public:
	~Skin();
	static void init();
	static Skin* get();
public:
	QColor bg;
	QColor titleBtn;
	QColor titleBtnHover;

	QColor year;
	QColor yearBtn;
	QColor yearBtnHover;
	QColor yearBtnBorder;
	QColor yearBtnToday;
	QColor yearBtnTodayHover;
	QColor yearBtnTodayBorder;

	QColor week;
	QColor day;
	QColor dayHover;
	QColor dayActive;
	QColor lunar;
	QColor dayNotCurMonth;
	QColor lunarNotCurMonth;
	QColor dot;
	QColor dayWorking;

	QColor switchText;

	QColor listHeader;
	QColor listItemText1;
	QColor listItemText2;
	QColor listItemBtn;
	QColor listItemBg;

	QColor tipInfo;
	QColor tipInfoBg;

	QColor menuBg;
	QColor menuHover;
	QColor menu;

private:
	Skin(QObject* parent = nullptr);
	void initBlack();
	void initWhite();
};

