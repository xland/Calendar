#pragma once
#include <TGUI/TGUI.hpp>
class CalendarSmall:public tgui::Grid
{
public:
	CalendarSmall();
	~CalendarSmall();
	static CalendarSmall::Ptr create();
private:
	void initTitle();
	void initDate();
};

