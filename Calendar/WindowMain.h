#pragma once
#include "WindowBase.h"
#include "CalendarModel.h"
class WindowMain : public WindowBase
{
public:
	WindowMain();
	~WindowMain();
	void initWinTitle();
private:
	bool isPosInCaption(const POINT& mousePos,const RECT& winRect) override;
	tgui::Grid::Ptr calendarGrid;
};

