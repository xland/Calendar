#pragma once
#include <blend2d.h>

class WindowBase;
class WidgetBase
{
public:
	WidgetBase(WindowBase* parent);
	~WidgetBase();
	virtual void Paint(BLContext* PaintCtx) {};
	WindowBase* parent;
protected:
private:
};

