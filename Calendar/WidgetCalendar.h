#pragma once
#include "WidgetBase.h"
class WidgetCalendar : public WidgetBase
{
public:
	WidgetCalendar();
	~WidgetCalendar();
private:
	void Paint(BLContext* PaintCtx) override;
};

