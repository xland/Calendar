#pragma once
#include <blend2d.h>
#include <string>
#include <functional>

class WindowBase;
class ViewBase
{
public:
	ViewBase(WindowBase* parent);
	~ViewBase();
	virtual void paint(BLContext* paintCtx) {};
	void changeSize(const int& w,const int& h);
	std::function<void(ViewBase* sender)> onMouseEnter;
	std::function<void(ViewBase* sender)> onMouseOut;
	std::function<void(ViewBase* sender)> onMouseUp;
	std::function<void(ViewBase* sender)> onMouseDown;
	void mouseMove(const int& x, const int& y);
	void mouseUp(const int& x, const int& y);
	void mouseDown(const int& x, const int& y);
	BLRgba32 backgroundColor;
	BLRgba32 foregroundColor;
	WindowBase* parent;
	BLBox box;
	bool isMouseEnter{ false };
	/// <summary>
	/// 0 left
	/// 1 right
	/// </summary>
	unsigned dockType{ 0 };
	bool isCursorHand{false};
protected:
private:
};

