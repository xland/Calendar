#pragma once
#include "WinBase.h"
class WinCalendar : public WinBase
{
public:
	WinCalendar();
	~WinCalendar();
private:
	void ctrlReady() override;
};

