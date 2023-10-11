#include "CalendarModel.h"
#include <thread>
#include <mutex>

std::mutex mylock;
static CalendarModel* calendarModel;

CalendarModel::CalendarModel() {
	std::time_t time = std::time(nullptr);
	tm now;
	localtime_s(&now, &time);
	auto secondCount = 86400 - now.tm_sec - 60 * now.tm_min - 3600 * now.tm_hour;
	currentDay.year = now.tm_year + 1900;
	currentDay.month = now.tm_mon + 1;
	currentDay.day = now.tm_mday;
	currentDay.weekNum = now.tm_wday == 0 ? 7 : now.tm_wday;
	currentDay.isInCurMonth = true;
	currentDay.isToday = true;
	setData();
	std::thread t(&CalendarModel::timerFunc, this, secondCount);
	t.detach();
}
CalendarModel::~CalendarModel() {

}

CalendarModel* CalendarModel::get() {
	return calendarModel;
}
void CalendarModel::init() {
	calendarModel = new CalendarModel();
}
void CalendarModel::dispose() {
	delete calendarModel;
}
void CalendarModel::timerFunc(int secondCount) {
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(secondCount + 6));
		mylock.lock();

		mylock.unlock();
	}
}

void CalendarModel::setData() {
	auto firstDay = std::chrono::year_month_day{ 
		std::chrono::year{currentDay.year},
		std::chrono::month{currentDay.month},
		std::chrono::day{1} };
	auto lastDay = getMonthLastDay(currentDay.year, currentDay.month);
	auto dayOfWeek = firstDay._Calculate_weekday() == 0 ? 7 : firstDay._Calculate_weekday();
	if (dayOfWeek != 1) {
		auto preMonthLastDay = getMonthLastDay(currentDay.year, currentDay.month - 1);
		unsigned temp = (unsigned)preMonthLastDay.day() - dayOfWeek + 1;
		for (size_t i = 1; i < dayOfWeek; i++)
		{
			CalendarItem item;
			item.year = (int)preMonthLastDay.year();
			item.month = (unsigned)preMonthLastDay.month();
			item.day = temp + i;
			item.weekNum = i;
			item.isInCurMonth = false;
			item.isToday = false;
			data.push_back(std::move(item));
		}
	}
	auto curMonthLastDay = (unsigned)lastDay.day();
	auto tempDayOfWeek = dayOfWeek;
	for (size_t i = 1; i <= curMonthLastDay; i++)
	{
		CalendarItem item;
		item.year = currentDay.year;
		item.month = currentDay.month;
		item.day = i;
		item.weekNum = tempDayOfWeek;
		item.isInCurMonth = true;
		item.isToday = (i==currentDay.day);
		data.push_back(std::move(item));
		tempDayOfWeek += 1;
		if (tempDayOfWeek == 8) {
			tempDayOfWeek = 1;
		}
	}
	auto lastEleNum = 42 - curMonthLastDay - dayOfWeek + 1;
	auto y = currentDay.year;
	auto m = currentDay.month+1;
	checkYearMonth(y, m);
	tempDayOfWeek = lastDay._Calculate_weekday() == 0 ? 7 : lastDay._Calculate_weekday();
	for (size_t i = 1; i <= lastEleNum; i++)
	{
		tempDayOfWeek += 1;
		if (tempDayOfWeek == 8) {
			tempDayOfWeek = 1;
		}
		CalendarItem item;
		item.year = y;
		item.month = m;
		item.day = i;
		item.weekNum = tempDayOfWeek;
		item.isInCurMonth = false;
		item.isToday = false;
		data.push_back(std::move(item));
	}
}

void CalendarModel::checkYearMonth(int& year, unsigned& month) {
	if (month < 1) {
		year = year - 1;
		month = 12;
	}
	else if (month > 12) {
		year = year + 1;
		month = 1;
	}
}

std::chrono::year_month_day CalendarModel::getMonthLastDay(int year, unsigned month) {
	checkYearMonth(year, month);
	std::chrono::year_month_day_last ymd{ std::chrono::year{year},
		std::chrono::month_day_last{std::chrono::month{month}} };
	std::chrono::year_month_day result{ ymd };
	return result;
}