#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QUuid>
#include "Schedules.h"
#include "ScheduleModel.h"
#include "../Eventer.h"
#include "../Schedule/DialogList.h"
#include "../Schedule/ScheduleEdit.h"

Schedules* schedules{nullptr};

Schedules::Schedules(QObject *parent) : QObject(parent)
{

}

Schedules::~Schedules()
{

}
void Schedules::initData()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Job order by StartTime desc;");
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return;
    }
    while (query.next()) {
        auto model = new ScheduleModel(this);
        model->Id = query.value("Id").toString();
        model->JobInfo = query.value("JobInfo").toString();
        model->StartTime = query.value("StartTime").toLongLong();
        model->RepeatType = query.value("RepeatType").toInt();
        data.append(model);
    }
}


void Schedules::delData(const QString& id)
{
    for (int i = data.size() - 1; i >= 0; --i)
    {
        if (data[i]->Id == id) {
            QSqlQuery query;
            query.prepare("DELETE FROM Job WHERE Id = ?;");
            query.addBindValue(id);
            auto flag = query.exec();
            delete data[i];
            data.removeAt(i);
            break;
        }
    }
}

void Schedules::editData(ScheduleModel* data)
{
    QSqlQuery query;
    query.prepare("UPDATE Job SET JobInfo = ?, StartTime = ?, RepeatType = ? WHERE Id = ?;");
    query.addBindValue(data->JobInfo);      // JobInfo
    query.addBindValue(data->StartTime);    // StartTime
    query.addBindValue(data->RepeatType);   // RepeatType
    query.addBindValue(data->Id);
    auto flag = query.exec();
    emit Eventer::get()->schedulesChange();
}

void Schedules::addData(ScheduleModel* d)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Job (Id, JobInfo, StartTime, RepeatType) VALUES (?, ?, ?, ?);");
    query.addBindValue(d->Id);
    query.addBindValue(d->JobInfo);    // JobInfo
    query.addBindValue(d->StartTime);  // StartTime
    query.addBindValue(d->RepeatType); // RepeatType
    auto flag = query.exec();
    data.insert(0, d);
}

ScheduleModel* Schedules::getData(const QString& id)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i]->Id == id) {
            return data[i];
        }
    }
    return nullptr;
}


bool Schedules::hasSchedule(const QDate& day)
{
    auto start = QDateTime(day, QTime(0, 0, 0));
    auto end = QDateTime(day, QTime(23, 59, 59, 999));

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i]->RepeatType == 0) { //不重复
            if (start.toSecsSinceEpoch() <= data[i]->StartTime && data[i]->StartTime <= end.toSecsSinceEpoch()) {
                return true;
            }
        }
        else if (data[i]->RepeatType == 1) { //每天
            return true;
        }
        else if (data[i]->RepeatType == 2) { //每个工作日
            int dayOfWeek = day.dayOfWeek();
            if (dayOfWeek == 6 || dayOfWeek == 7) {
                continue;
            }
            return true;
        }
        else if (data[i]->RepeatType == 3) { //每周几
            auto dayOfWeek = QDateTime::fromSecsSinceEpoch(data[i]->StartTime).date().dayOfWeek();
            if (dayOfWeek != day.dayOfWeek()) {
                continue;                
            }
            return true;
        }
        else if (data[i]->RepeatType == 4) { //每月第N天
            auto dayOfMonth = QDateTime::fromSecsSinceEpoch(data[i]->StartTime).date().day();
            if (dayOfMonth != day.day()) {
                continue;
            }
            return true;
        }
        else if (data[i]->RepeatType == 5) { //每年N月N日
            auto sDay = QDateTime::fromSecsSinceEpoch(data[i]->StartTime).date();
            auto month = sDay.month();
            auto dayOfMonth = sDay.day();
            if (dayOfMonth != day.day() || month != day.month()) {
                continue;
            }
            return true;
        }
    }
    return false;
}

QList<ScheduleModel*> Schedules::getData(const QDate& startD, const QDate& endD)
{
    auto data = getDataAll();
    QList<ScheduleModel*> list;
    auto start = QDateTime(startD, QTime(0, 0, 0));
    auto end = QDateTime(endD, QTime(23, 59, 59, 999));
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i]->RepeatType == 0) { //不重复
            if (start.toSecsSinceEpoch() <= data[i]->StartTime && data[i]->StartTime <= end.toSecsSinceEpoch()) {
                list.append(data[i]);
            }
        }
        else if (data[i]->RepeatType == 1) { //每天
            list.append(data[i]);
        }
        else if (data[i]->RepeatType == 2) { //每个工作日
            bool isStartWeekend = (startD.dayOfWeek() == Qt::Saturday || startD.dayOfWeek() == Qt::Sunday);
            bool isEndWeekend = (endD.dayOfWeek() == Qt::Saturday || endD.dayOfWeek() == Qt::Sunday);
            if (!isStartWeekend || !isEndWeekend) {
                list.append(data[i]);
            }
            else if (startD.daysTo(endD) > 2) {
                list.append(data[i]);
            }
        }
        else if (data[i]->RepeatType == 3) { //每周几
            auto dayOfWeek = QDateTime::fromSecsSinceEpoch(data[i]->StartTime).date().dayOfWeek();
            if (startD.daysTo(endD) > 7) {
                list.append(data[i]);
            }
            else {
                for (QDate date = startD; date <= endD; date = date.addDays(1)) {
                    if (date.dayOfWeek() == dayOfWeek) {
                        list.append(data[i]);
                        break;
                    }
                }
            }
        }
        else if (data[i]->RepeatType == 4) { //每月第N天
            auto dayOfMonth = QDateTime::fromSecsSinceEpoch(data[i]->StartTime).date().day();
            if (startD.daysTo(endD) > 31) {
                list.append(data[i]);
            }
            else {
                for (QDate date = startD; date <= endD; date = date.addDays(1)) {
                    if (date.day() == dayOfMonth) {
                        list.append(data[i]);
                        break;
                    }
                }
            }
        }
        else if (data[i]->RepeatType == 5) { //每年N月N日
            auto sDay = QDateTime::fromSecsSinceEpoch(data[i]->StartTime).date();
            auto month = sDay.month();
            auto dayOfMonth = sDay.day();
            if (startD.daysTo(endD) > 366) {
                list.append(data[i]);
            }
            else if (startD.month() < month && month < endD.month()) {
                list.append(data[i]);
            }
            else if(startD.month() == month && month == endD.month()){
                if (startD.day() <= dayOfMonth && dayOfMonth <= endD.day()) {
                    list.append(data[i]);
                }
            }
        }
    }
    return list;
}

QList<ScheduleModel*> Schedules::getDataAll()
{
    QList<ScheduleModel*> data;
    QSqlQuery query;
    query.prepare("SELECT * FROM Job order by StartTime desc;");
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    while (query.next()) {
        auto model = new ScheduleModel(this);
        model->Id = query.value("Id").toString();
        model->JobInfo = query.value("JobInfo").toString();
        model->StartTime = query.value("StartTime").toLongLong();
        model->RepeatType = query.value("RepeatType").toInt();
        data.append(model);
    }
    return data;
}

void Schedules::init() 
{
    schedules = new Schedules(qApp);
    schedules->initData();
}
Schedules* Schedules::get() 
{
    return schedules;
}


