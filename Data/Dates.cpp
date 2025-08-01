#include <QApplication>
#include "Dates.h"
#include "DateModel.h"
#include "NongLi.h"
#include "Schedules.h"

Dates* ins;

Dates::Dates(QObject *parent) : QObject(parent)
{
    for (int i = 0; i < 42; i++)
    {
        dates.append(new DateModel(this));
    }
    initOneMonthDate(QDate::currentDate());
}

Dates::~Dates()
{

}

void Dates::init()
{
    ins = new Dates(qApp);
}
Dates* Dates::get()
{
    return ins;
}
void Dates::refresh() {
    ins->initOneMonthDate(ins->dates[21]->date);
}
void Dates::initOneMonthDate(const QDate& tarDate)
{
    int year = tarDate.year();
    int month = tarDate.month(); // 1~12
    int dateIndex = 0;
    auto curDay = QDate::currentDate();
    auto schedules = Schedules::get();
    // 上个月最后一天
    QDate preMonthLastDay = QDate(year, month, 1).addDays(-1);
    int weekIndex = preMonthLastDay.dayOfWeek(); // 1 = Monday, 7 = Sunday
    if (weekIndex < 7) {
        int startDay = preMonthLastDay.day() - weekIndex + 1;
        for (int i = startDay; i <= preMonthLastDay.day(); ++i) {
            auto year = preMonthLastDay.year();
            auto month = preMonthLastDay.month();
            auto& tar = dates[dateIndex];
            tar->date = QDate(year, month, i);
            tar->isCurMonth = false;
            tar->lunar = NongLi::solar2lunar(year, month, i).iDayCn;
            tar->isToday = (tar->date == curDay);
            tar->hasSchedule = schedules->hasSchedule(tar->date);
            dateIndex += 1;
        }
    }

    // 当前月天数
    QDate curMonthFirstDay(year, month, 1);
    QDate curMonthLastDay = curMonthFirstDay.addMonths(1).addDays(-1);
    for (int i = 1; i <= curMonthLastDay.day(); ++i) {
        auto& tar = dates[dateIndex];
        tar->date = QDate(year, month, i);
        tar->isCurMonth = true;
        tar->lunar = NongLi::solar2lunar(year, month, i).iDayCn;
        tar->isToday = (tar->date == curDay);
        tar->hasSchedule = schedules->hasSchedule(tar->date);
        dateIndex += 1;
    }

    // 下个月补足剩余天数
    int lastDayCount = 42 - dateIndex;
    if (lastDayCount > 0) {
        QDate nextMonthFirstDay = curMonthFirstDay.addMonths(1);
        for (int i = 1; i <= lastDayCount; ++i) {
            auto year = nextMonthFirstDay.year();
            auto month = nextMonthFirstDay.month();
            auto& tar = dates[dateIndex];
            tar->date = QDate(year, month, i);
            tar->isCurMonth = false;
            tar->lunar = NongLi::solar2lunar(year, month, i).iDayCn;
            tar->isToday = (tar->date == curDay);
            tar->hasSchedule = schedules->hasSchedule(tar->date);
            dateIndex += 1;
        }
    }
    emit datesChanged();
}
