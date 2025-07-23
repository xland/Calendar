#include <QUuid>
#include "ScheduleModel.h"

ScheduleModel::ScheduleModel(QObject* parent) : QObject(parent)
{

}

ScheduleModel::ScheduleModel(const QString& JobInfo, const long long& StartTime, const int& RepeatType, QObject* parent) : QObject(parent), 
JobInfo{ JobInfo }, StartTime{ StartTime }, RepeatType{ RepeatType }, Id{ QUuid::createUuid().toString().mid(1, 36) }
{
    
}

ScheduleModel::~ScheduleModel()
{}

