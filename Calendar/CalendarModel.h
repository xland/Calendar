#pragma once
#include "CalendarItem.h"
#include <chrono>
class CalendarModel
{
public:	
	~CalendarModel();	
	static CalendarModel* get();
	static void init();
	static void dispose();
	CalendarItem currentDay;
	std::vector<CalendarItem> data;
private:
	CalendarModel();
	void setData();
	void timerFunc(int secondCount);
	void checkYearMonth(int& year1, unsigned& month1);
	std::chrono::year_month_day getMonthLastDay(int year1, unsigned month1);
};

