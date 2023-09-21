#pragma once
#include "WindowBase.h"
class WindowMain : public WindowBase
{
public:
	WindowMain();
	~WindowMain();
private:
	void OnPaint() override;
	int OnHitTest(const int& x, const int& y) override;
};

