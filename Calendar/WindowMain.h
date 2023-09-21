#pragma once
#include "WindowBase.h"
class WindowMain : public WindowBase
{
public:
	WindowMain();
	~WindowMain();
private:
	void OnPaint() override;
	bool CaptionTest(const int& x, const int& y) override;
	void ProcessWindowMsg(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;
};

