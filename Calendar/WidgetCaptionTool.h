#pragma once
#include "WidgetBase.h"
class WidgetCaptionTool : public WidgetBase
{
public:
	WidgetCaptionTool(WindowBase* parent);
	~WidgetCaptionTool();
	void Paint(BLContext* paintCtx) override;
private:
};

