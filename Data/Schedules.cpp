#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include "Schedules.h"
#include "ScheduleModel.h"
#include "../Eventer.h"

Schedules* schedules{nullptr};

Schedules::Schedules(QObject *parent) : QObject(parent)
{

}

Schedules::~Schedules()
{

}

void Schedules::addData(const QString& JobInfo, const long long& StartTime, const int& RepeatType)
{
    auto d = new ScheduleModel(JobInfo, StartTime, RepeatType, this);
    data.insert(0, d);
    Eventer::get()->fire("refreshData", d);
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

void Schedules::initData()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Job order by StartTime desc");
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return;
    }
    while (query.next()) {
        auto model = new ScheduleModel(query, this);
        data.append(model);
    }
}
