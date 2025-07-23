#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QUuid>
#include "Schedules.h"
#include "ScheduleModel.h"
#include "../Eventer.h"
#include "../Schedule/DialogSchedule.h"
#include "../Schedule/ScheduleEdit.h"

Schedules* schedules{nullptr};

Schedules::Schedules(QObject *parent) : QObject(parent)
{

}

Schedules::~Schedules()
{

}

void Schedules::addData(const QString& JobInfo, const long long& StartTime, const int& RepeatType)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i]->isSelected) {
            data[i]->isSelected = false;
            break;
        }
    }
    auto d = new ScheduleModel(JobInfo, StartTime, RepeatType, this);
    d->isSelected = true;
    QSqlQuery query;
    query.prepare("INSERT INTO Job (Id, JobInfo, StartTime, RepeatType) VALUES (?, ?, ?, ?);");
    query.addBindValue(d->Id);
    query.addBindValue(d->JobInfo);    // JobInfo
    query.addBindValue(d->StartTime);  // StartTime
    query.addBindValue(d->RepeatType); // RepeatType
    auto flag = query.exec();
    data.insert(0, d);
    emit Eventer::get()->schedulesChange();    
}

void Schedules::delData(ScheduleModel* item)
{
    bool isDelSelected{ false };
    for (int i = data.size() - 1; i >= 0; --i)
    {
        auto d = data[i];
        if (d->Id == item->Id) {
            if (item->isSelected) {
                isDelSelected = true;
            }
            QSqlQuery query;
            query.prepare("DELETE FROM Job WHERE Id = ?;");
            query.addBindValue(item->Id);
            auto flag = query.exec();
            delete data[i];
            data.removeAt(i);
            break;
        }
    }
    if (isDelSelected && data.size() > 0) {
        data[0]->isSelected = true;
    }
    emit Eventer::get()->schedulesChange();
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

ScheduleModel* Schedules::getSelectedData()
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i]->isSelected) {
            return data[i];
        }
    }
    return nullptr;
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
        auto model = new ScheduleModel(this);
        model->Id = query.value("Id").toString();
        model->JobInfo = query.value("JobInfo").toString();
        model->StartTime = query.value("StartTime").toLongLong();
        model->RepeatType = query.value("RepeatType").toInt();
        data.append(model);
    }
    if (data.size() > 0) {
        data[0]->isSelected = true;
    }
}
