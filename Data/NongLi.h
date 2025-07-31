#pragma once

#include <QMap>
#include <QString>
#include <QDate>

struct DateInfo {
    QDate date;
    QString festival;     // 节日
    QString animal;       // 生肖
    QString iMonthCn;     // 中文农历月
    QString iDayCn;       // 中文农历日
    QString gzYear;       // 干支年
    bool isLeap;          // 是否闰月
};

class NongLi {
private:
    static int leapMonth(int y);
    static int leapDays(int y);
    static int monthDays(int y, int m);
    static int lYearDays(int y);
    static int solarDays(int y, int m);
    static QString toGanZhiYear(int lYear);
    static QString getAnimal(int y);
    static QString toChinaMonth(int m);
    static QString toChinaDay(int d);
public:
    static DateInfo solar2lunar(int y, int m, int d);    
};
