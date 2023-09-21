#pragma once
#include "WidgetBase.h"
class WidgetCaptionTool : public WidgetBase
{
public:
	WidgetCaptionTool();
	~WidgetCaptionTool();
private:
	void Paint(BLContext* PaintCtx) override;
};

