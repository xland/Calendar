#pragma once
#include "WindowBase.h"
class WindowMain : public WindowBase
{
public:
	WindowMain();
	~WindowMain();
private:
	bool isPosInCaption(const POINT& mousePos,const RECT& winRect) override;
};

