#include "ScheduleModel.h"

ScheduleModel::ScheduleModel(const QSqlQuery& query, QObject *parent) : QObject(parent)
{
    Id = query.value("Id").toString();
    JobInfo = query.value("JobInfo").toString();
    StartTime = query.value("StartTime").toLongLong();
    RepeatType = query.value("RepeatType").toInt();
}

ScheduleModel::~ScheduleModel()
{}

