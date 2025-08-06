#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QMessageBox>
#include <QUuid>
#include <climits>

#include "Schedules.h"
#include "ScheduleModel.h"
#include "../Schedule/DialogList.h"
#include "../Embed/Alert.h"

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

QList<ScheduleModel*> Schedules::getData(const QDate& startD, const QDate& endD,const QString& keyword)
{
    QList<ScheduleModel*> list;
    QSqlQuery query;
    auto start = QDateTime(startD, QTime(0, 0, 0));
    auto end = QDateTime(endD, QTime(23, 59, 59, 999));
    if (keyword.isEmpty()) {
        query.prepare("SELECT * FROM Schedule where UpcomingTime > ? And UpcomingTime < ? order by UpcomingTime asc");
    }
    else {
        query.prepare("SELECT * FROM Schedule where Schedule LIKE ? UpcomingTime > ? And UpcomingTime < ? order by UpcomingTime asc");
        query.addBindValue("%"+keyword+"%");
    }    
    query.addBindValue(start.toSecsSinceEpoch());
    query.addBindValue(end.toSecsSinceEpoch());
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    while (query.next()) {
        auto data = new ScheduleModel(query);
        list.append(data);
    }
    return list;
}

QList<ScheduleModel*> Schedules::getUpcomingData(const int& count)
{
    QList<ScheduleModel*> list;
    QSqlQuery query;
    query.prepare("SELECT * FROM Schedule where IsExpire = 0 AND UpcomingTime > ? order by UpcomingTime ASC LIMIT ?");
    auto now = QDateTime::currentDateTime().toSecsSinceEpoch();
    query.addBindValue(now);
    query.addBindValue(count);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return list;
    }
    while (query.next()) {
        auto data = new ScheduleModel(query);
        list.append(data);
    }
    return list;
}

QList<ScheduleModel*> Schedules::getUpcomingData(const int& count, qint64 time) {
    QList<ScheduleModel*> list;
    QSqlQuery query;
    query.prepare("SELECT * FROM Schedule where IsExpire = 0 AND UpcomingTime > ? order by UpcomingTime ASC LIMIT ?");
    query.addBindValue(time);
    query.addBindValue(count);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return list;
    }
    while (query.next()) {
        auto data = new ScheduleModel(query);
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
    query.addBindValue(false); //找到未过期的日程，这里主要用于过滤单次发生的日程
    query.addBindValue(curTime); //找到下次发生时间早于当前时间的日程
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    while(query.next()) {
        auto data = new ScheduleModel(query);     
        if (reply == QMessageBox::Yes) {
            Alert alert(data->Id);
            alert.exec();
        }
        data->setUpcomingTime();
        if (data->RepeatType == 1) {
            data->IsExpire = true;
        }
        data->update();
    }
}