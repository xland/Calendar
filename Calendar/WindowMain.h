#pragma once
#include "WindowBase.h"
class WindowMain : public WindowBase
{
public:
	WindowMain();
	~WindowMain();
	void initWinTitle();
	void initTitleBarBtns();
	void initCalendarTitle();
	void initCalendarDate();
private:
	bool isPosInCaption(const POINT& mousePos,const RECT& winRect) override;
	tgui::Grid::Ptr calendarGrid;
};

