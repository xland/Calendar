#pragma once

struct CalendarItem
{
	int year;
	unsigned month;
	unsigned day;
	unsigned weekNum;
	bool isToday;
	bool isInCurMonth;
};
