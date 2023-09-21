#pragma once
#include <blend2d.h>
class WidgetBase
{
public:
	WidgetBase();
	~WidgetBase();
protected:
	virtual void Paint(BLContext* PaintCtx) {};
private:
};

