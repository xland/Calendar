#pragma once
#include "WidgetBase.h"
class WidgetCalendar : public WidgetBase
{
public:
	WidgetCalendar(WindowBase* parent);
	~WidgetCalendar();
	void Paint(BLContext* paintCtx) override;
private:
};

