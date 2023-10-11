#pragma once
#include <Windows.h>
#include <TGUI/TGUI.hpp>
class TitleBarBtns:public tgui::HorizontalLayout
{
public:
	TitleBarBtns();
	~TitleBarBtns();
	static TitleBarBtns::Ptr create();
	void close();
	void minimize();
	void maximizeRestore();
private:
};

