#pragma once
#include "ViewBase.h"

class ViewCalendar : public ViewBase
{
public:
	ViewCalendar(WindowBase* parent);
	~ViewCalendar();
	void paint(BLContext* paintCtx) override;
private:
};

