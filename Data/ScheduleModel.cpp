#include <QUuid>
#include <QDateTime>
#include <QSqlError>
#include "ScheduleModel.h"
#include "Dates.h"
#include "TickTock.h"
#include "Schedules.h"

ScheduleModel::ScheduleModel(QObject* parent) : QObject(parent), Id{ QUuid::createUuid().toString().mid(1, 36) }
{

}
ScheduleModel::ScheduleModel(QSqlQuery& query, QObject* parent) : QObject(parent)
{
    initByQuery(query);
}

ScheduleModel::ScheduleModel(const QString& id, QObject* parent) : QObject(parent)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Schedule where Id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    if (query.next()) {
        initByQuery(query);
    }
}

ScheduleModel::~ScheduleModel()
{

}

void ScheduleModel::insert()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Schedule (Id,Schedule,IsExpire,CreateTime,FirstTime,UpcomingTime,RepeatType,Year,Month,Day,Time) VALUES (?,?,?,?,?,?,?,?,?,?,?)");
    query.addBindValue(Id);
    query.addBindValue(Schedule);
    query.addBindValue(IsExpire);
    query.addBindValue(CreateTime);
    query.addBindValue(FirstTime);
    query.addBindValue(UpcomingTime);
    query.addBindValue(RepeatType);
    query.addBindValue(Year);
    query.addBindValue(Month);
    query.addBindValue(Day);
    query.addBindValue(Time);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    emit Schedules::get()->scheduleChanged();
    Dates::get()->refresh();
}

void ScheduleModel::update()
{
    QSqlQuery query;
    query.prepare("UPDATE Schedule SET Schedule=?,IsExpire=?,FirstTime=?,UpcomingTime=?,RepeatType=?,Year=?,Month=?,Day=?,Time=? WHERE Id=?");
    query.addBindValue(Schedule);
    query.addBindValue(IsExpire);
    query.addBindValue(FirstTime);
    query.addBindValue(UpcomingTime);
    query.addBindValue(RepeatType);
    query.addBindValue(Year);
    query.addBindValue(Month);
    query.addBindValue(Day);
    query.addBindValue(Time);
    query.addBindValue(Id);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    emit Schedules::get()->scheduleChanged();
    Dates::get()->refresh();
}

void ScheduleModel::del()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Schedule WHERE Id = ?");
    query.addBindValue(Id);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    emit Schedules::get()->scheduleChanged();
    Dates::get()->refresh();
}

void ScheduleModel::del(const QString& id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Schedule WHERE Id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    emit Schedules::get()->scheduleChanged();
    Dates::get()->refresh();
}

void ScheduleModel::setUpcomingTime()
{
    QDateTime dt = QDateTime::fromSecsSinceEpoch(UpcomingTime);
    QDateTime curDt = QDateTime::currentDateTime();
    QDateTime upcomingDt;
    if (RepeatType == 1) { //不重复
        upcomingDt = dt;
    }
    else if (RepeatType == 2) { //每天
        if (dt.time() < curDt.time()) {
            upcomingDt = QDateTime(curDt.addDays(1).date(), dt.time()); //明天这个时间
        }
        else
        {
            upcomingDt = QDateTime(curDt.date(), dt.time()); //今天这个时间
        }
    }
    else if (RepeatType == 3) { //每个工作日
        auto dayOfWeek = curDt.date().dayOfWeek();
        if (dayOfWeek == 6) { //当前时间为周六
            upcomingDt = QDateTime(curDt.addDays(2).date(), dt.time()); //下周一这个时间
        }
        else if (dayOfWeek == 7) { //当前时间为周日
            upcomingDt = QDateTime(curDt.addDays(1).date(), dt.time()); //下周一这个时间
        }
        else //当前时间为工作日
        {
            if (dt.time() < curDt.time()) {
                auto tempDt = curDt.addDays(1).date();//明天这个时间
                if (tempDt.dayOfWeek() == 6) {
                    tempDt = curDt.addDays(2).date(); //如果明天是周六，那么定位到下周一
                }
                upcomingDt = QDateTime(tempDt, dt.time());
            }
            else
            {
                upcomingDt = QDateTime(curDt.date(), dt.time()); //今天这个时间
            }
        }
    }
    else if (RepeatType == 4) { //每周几
        auto dayOfWeek = curDt.date().dayOfWeek();
        auto dtDayOfWeek = dt.date().dayOfWeek();
        if (dayOfWeek == dtDayOfWeek) {
            if (dt.time() < curDt.time()) {
                upcomingDt = QDateTime(curDt.addDays(7).date(), dt.time()); //下周这个时间
            }
            else
            {
                upcomingDt = QDateTime(curDt.date(), dt.time()); //今天这个时间
            }
        }
        else if (dayOfWeek < dtDayOfWeek) {
            upcomingDt = QDateTime(curDt.addDays(dtDayOfWeek - dayOfWeek).date(), dt.time());
        }
        else {
            upcomingDt = QDateTime(curDt.addDays(7 - (dayOfWeek - dtDayOfWeek)).date(), dt.time());
        }
    }
    else if (RepeatType == 5) { //每月第几天
        auto dayDt = dt.date().day();
        auto tempDt = curDt.date();
        if (curDt.date().day() != dayDt)
        {
            for (int i = 0; i < 61; i++) //逐一找下一天，不会超过两个月
            {
                tempDt = tempDt.addDays(1);
                if (tempDt.day() == dayDt) {
                    break;
                }
            }
        }
        else if (dt.time() < curDt.time()) {
            tempDt = tempDt.addDays(26);
            for (int i = 0; i < 61; i++) //逐一找下一天，不会超过两个月
            {
                tempDt = tempDt.addDays(1);
                if (tempDt.day() == dayDt) {
                    break;
                }
            }
        }
        upcomingDt = QDateTime(tempDt, dt.time());
    }
    else if (RepeatType == 6) { //每年N月N日
        if (dt < curDt) {
            auto date = dt.date();
            auto day = date.day();
            QDateTime temp = QDateTime(QDate(date.year() + 1, date.month(), day), dt.time()); //类似这样的2025-02-29日期会被静默修复为：2025-03-01
            for (int i = 0; i < 8; i++) //不会超过两个闰年
            {
                if (temp.date().day() == day) {
                    break;
                }
                else {
                    temp = QDateTime(QDate(temp.date().year() + 1, date.month(), day), dt.time());
                }
            }
            upcomingDt = temp;
        }
        else
        {
            upcomingDt = dt;
        }
    }
    UpcomingTime = upcomingDt.toSecsSinceEpoch();
    Year = upcomingDt.date().year();
    Month = upcomingDt.date().month();
    Day = upcomingDt.date().day();
    Time = upcomingDt.time().msecsSinceStartOfDay();
}

void ScheduleModel::setNextTime() {
    QDateTime dt = QDateTime::fromSecsSinceEpoch(UpcomingTime);
    QDateTime curDt = QDateTime::currentDateTime();
    QDateTime upcomingDt;
    if (RepeatType == 1) { //不重复
        upcomingDt = dt;
    }
    else if (RepeatType == 2) { //每天
        upcomingDt = QDateTime(curDt.date().addDays(1), dt.time());
    }
    else if (RepeatType == 3) { //每个工作日
        auto tempDt = curDt.addDays(1).date();
        if (tempDt.dayOfWeek() == 6) {
            tempDt = curDt.addDays(2).date(); //如果明天是周六，那么定位到下周一
        }
        upcomingDt = QDateTime(tempDt, dt.time());
    }
    else if (RepeatType == 4) { //每周几
        upcomingDt = QDateTime(curDt.addDays(7).date(), dt.time());
    }
    else if (RepeatType == 5) { //每月第几天
        auto dayDt = dt.date().day();
        auto tempDt = curDt.date().addDays(26);
        for (int i = 1; i < 61; i++) //逐一找下一天，不会超过两个月
        {
            tempDt = tempDt.addDays(1);
            if (tempDt.day() == dayDt) {
                break;
            }
        }
        upcomingDt = QDateTime(tempDt, dt.time());
    }
    else if (RepeatType == 6) { //每年N月N日
        auto date = dt.date();
        auto day = date.day();
        QDateTime temp = QDateTime(QDate(date.year() + 1, date.month(), day), dt.time()); //类似这样的2025-02-29日期会被静默修复为：2025-03-01
        for (int i = 0; i < 8; i++) //不会超过两个闰年
        {
            if (temp.date().day() == day) {
                break;
            }
            else {
                temp = QDateTime(QDate(temp.date().year() + 1, date.month(), day), dt.time());
            }
        }
        upcomingDt = temp;
    }
    UpcomingTime = upcomingDt.toSecsSinceEpoch();
    Year = upcomingDt.date().year();
    Month = upcomingDt.date().month();
    Day = upcomingDt.date().day();
    Time = upcomingDt.time().msecsSinceStartOfDay();
}

void ScheduleModel::initByQuery(QSqlQuery& query)
{
    Id = query.value("Id").toString();
    Schedule = query.value("Schedule").toString();
    RepeatType = query.value("RepeatType").toInt();
    CreateTime = query.value("CreateTime").toLongLong();
    FirstTime = query.value("FirstTime").toLongLong();
    UpcomingTime = query.value("UpcomingTime").toLongLong();
    Year = query.value("Year").toLongLong();
    Month = query.value("Month").toLongLong();
    Day = query.value("Day").toLongLong();
    Time = query.value("Time").toLongLong();
    IsExpire = query.value("IsExpire").toBool();
}

