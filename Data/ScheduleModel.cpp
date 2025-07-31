#include <QUuid>
#include "ScheduleModel.h"

ScheduleModel::ScheduleModel(QObject* parent) : QObject(parent), Id{ QUuid::createUuid().toString().mid(1, 36) }
{

}
ScheduleModel::ScheduleModel(QSqlQuery& query, QObject* parent) : QObject(parent)
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

ScheduleModel::~ScheduleModel()
{}

