#include <QUuid>
#include "ScheduleModel.h"

ScheduleModel::ScheduleModel(const QSqlQuery& query, QObject *parent) : QObject(parent)
{
    Id = query.value("Id").toString();
    JobInfo = query.value("JobInfo").toString();
    StartTime = query.value("StartTime").toLongLong();
    RepeatType = query.value("RepeatType").toInt();
}

ScheduleModel::ScheduleModel(const QString& JobInfo, const long long& StartTime, const int& RepeatType, QObject* parent) : QObject(parent), 
JobInfo{ JobInfo }, StartTime{ StartTime }, RepeatType{ RepeatType }, Id{ QUuid::createUuid().toString().mid(1, 36) }
{
    QSqlQuery query;
    query.prepare("INSERT INTO Job (Id, JobInfo, StartTime, RepeatType) VALUES (?, ?, ?, ?);");
    auto uuid = QUuid::createUuid().toString().mid(1, 36);
    query.addBindValue(uuid);
    query.addBindValue("日程内容......");    // JobInfo
    query.addBindValue(StartTime); // StartTime
    query.addBindValue(0);         // RepeatType
    auto flag = query.exec();
}

ScheduleModel::~ScheduleModel()
{}

