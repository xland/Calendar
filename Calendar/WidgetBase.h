#pragma once
#include <blend2d.h>
#include <string>
#include <functional>

class WindowBase;
class WidgetBase
{
public:
	WidgetBase(WindowBase* parent);
	~WidgetBase();
	virtual void paint(BLContext* paintCtx) {};
	std::function<void(WidgetBase* sender)> onMouseEnter;
	std::function<void(WidgetBase* sender)> onMouseOut;
	std::function<void(WidgetBase* sender)> onMouseUp;
	std::function<void(WidgetBase* sender)> onMouseDown;
	bool MouseMove(const int& x, const int& y);
	bool MouseUp(const int& x, const int& y);
	bool MouseDown(const int& x, const int& y);
	BLRgba32 backgroundColor;
	BLRgba32 foregroundColor;
	WindowBase* parent;
	BLBox box;
	std::string text;
	bool isMouseEnter{ false };
protected:
private:
};

