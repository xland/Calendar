#pragma once
#include "ViewBase.h"
#include <memory>

class ViewCalendar : public ViewBase
{
public:
	ViewCalendar(WindowBase* parent);
	~ViewCalendar();
	void paint(BLContext* paintCtx) override;
	static std::shared_ptr<ViewCalendar> createCalendar(WindowBase* parent);
private:
};

