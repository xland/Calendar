#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QMessageBox>
#include <QUuid>
#include <climits>

#include "Schedules.h"
#include "ScheduleModel.h"
#include "../Schedule/DialogList.h"

Schedules* schedules{nullptr};

Schedules::Schedules(QObject *parent) : QObject(parent)
{
    updateUpcomingSchedule();
}

Schedules::~Schedules()
{

}
void Schedules::init()
{
    schedules = new Schedules(qApp);
}
Schedules* Schedules::get()
{
    return schedules;
}

void Schedules::setUpcomingTime(ScheduleModel* data)
{
    QDateTime dt = QDateTime::fromSecsSinceEpoch(data->UpcomingTime);
    QDateTime curDt = QDateTime::currentDateTime();
    QDateTime upcomingDt;
    if (data->RepeatType == 1) { //不重复
        upcomingDt = dt;
    }
    else if (data->RepeatType == 2) { //每天
        if (dt.time() < curDt.time()) {
            upcomingDt = QDateTime(curDt.addDays(1).date(), dt.time()); //明天这个时间
        }
        else
        {
            upcomingDt = QDateTime(curDt.date(), dt.time()); //今天这个时间
        }
    }
    else if (data->RepeatType == 3) { //每个工作日
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
    else if (data->RepeatType == 4) { //每周几
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
    else if (data->RepeatType == 5) { //每月第几天
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
    else if (data->RepeatType == 6) { //每年N月N日
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
    data->UpcomingTime = upcomingDt.toSecsSinceEpoch();
    data->Year = upcomingDt.date().year();
    data->Month = upcomingDt.date().month();
    data->Day = upcomingDt.date().day();
    data->Time = upcomingDt.time().msecsSinceStartOfDay();

}

void Schedules::delData(const QString& id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Schedule WHERE Id = ?;");
    query.addBindValue(id);
    auto flag = query.exec();
}

void Schedules::editData(ScheduleModel* data)
{
    QSqlQuery query;
    query.prepare("UPDATE Schedule SET Schedule=?,IsExpire=?,FirstTime=?,UpcomingTime=?,RepeatType=?,Year=?,Month=?,Day=?,Time=? WHERE Id=?");
    query.addBindValue(data->Schedule);
    query.addBindValue(data->IsExpire);
    query.addBindValue(data->FirstTime);
    query.addBindValue(data->UpcomingTime);
    query.addBindValue(data->RepeatType);
    query.addBindValue(data->Year);
    query.addBindValue(data->Month);
    query.addBindValue(data->Day);
    query.addBindValue(data->Time);
    query.addBindValue(data->Id);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    else
    {
        emit scheduleChanged();
    }
}

void Schedules::addData(ScheduleModel* d)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Schedule (Id,Schedule,IsExpire,CreateTime,FirstTime,UpcomingTime,RepeatType,Year,Month,Day,Time) VALUES (?,?,?,?,?,?,?,?,?,?,?);");
    query.addBindValue(d->Id);
    query.addBindValue(d->Schedule);
    query.addBindValue(d->IsExpire);
    query.addBindValue(d->CreateTime);
    query.addBindValue(d->FirstTime);
    query.addBindValue(d->UpcomingTime);
    query.addBindValue(d->RepeatType);
    query.addBindValue(d->Year);
    query.addBindValue(d->Month);
    query.addBindValue(d->Day);
    query.addBindValue(d->Time);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    else
    {
        emit scheduleChanged();
    }
}

bool Schedules::hasSchedule(const QDate& date)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Schedule WHERE Year = ? AND Month = ? AND Day = ?");
    query.addBindValue(date.year());
    query.addBindValue(date.month());
    query.addBindValue(date.day());
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return false;
    }
    if (query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            return true;
        }
    }
    return false;
}

ScheduleModel* Schedules::getData(const QString& id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Schedule where Id = ?;");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return nullptr;
    }
    if (query.next()) {
        auto model = new ScheduleModel(query,this);
        return model;
    }
    return nullptr;
}

QList<ScheduleModel*> Schedules::getData(const QDate& startD, const QDate& endD,const QString& keyword)
{
    QList<ScheduleModel*> list;
    QSqlQuery query;
    auto start = QDateTime(startD, QTime(0, 0, 0));
    auto end = QDateTime(endD, QTime(23, 59, 59, 999));
    if (keyword.isEmpty()) {
        query.prepare("SELECT * FROM Schedule where UpcomingTime > ? And UpcomingTime < ?");
    }
    else {
        query.prepare("SELECT * FROM Schedule where Schedule LIKE ? UpcomingTime > ? And UpcomingTime < ?");
        query.addBindValue("%"+keyword+"%");
    }    
    query.addBindValue(start.toSecsSinceEpoch());
    query.addBindValue(end.toSecsSinceEpoch());
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    while (query.next()) {
        auto data = new ScheduleModel(query,this);
        list.append(data);
    }
    return list;
}

void Schedules::updateUpcomingSchedule()
{
    auto curTime = QDateTime::currentDateTime().toSecsSinceEpoch();
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Schedule WHERE IsExpire = ? AND UpcomingTime < ?");
    query.addBindValue(false);  //找到未过期的日程，这里主要用于过滤单次发生的日程
    query.addBindValue(curTime); //找到下次发生时间早于当前时间的日程
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return;
    }
    QMessageBox::StandardButton reply{ QMessageBox::Yes };
    if (query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            reply = QMessageBox::question(nullptr, "过期日程提醒",
                QString("存在 %1 条过期但未提醒的日程，现在需要为您逐一显示这些日程吗？").arg(count),
                QMessageBox::Yes | QMessageBox::No);
        }
        else {
            return;
        }
    }
    query.prepare("SELECT * FROM Schedule where IsExpire = ? AND UpcomingTime < ?");
    query.addBindValue(0); //找到未过期的日程，这里主要用于过滤单次发生的日程
    query.addBindValue(curTime); //找到下次发生时间早于当前时间的日程
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    while(query.next()) {
        auto data = new ScheduleModel(query,this);     
        if (reply == QMessageBox::Yes) {
            QMessageBox::information(nullptr, "日程提醒", data->Schedule);
        }
        setUpcomingTime(data);
        if (data->RepeatType == 1) {
            data->IsExpire = true;
        }
        editData(data);
    }
}






