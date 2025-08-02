#include <QApplication>
#include <QSqlError>
#include <QSqlQuery>
#include "SettingModel.h"

SettingModel* setting;

SettingModel::SettingModel(QObject *parent) : QObject(parent)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Setting LIMIT 1");
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
    if (query.next()) {
        X = query.value("X").toInt();
        Y = query.value("Y").toInt();
        AlertBefore = query.value("AlertBefore").toInt();
    }
}

SettingModel::~SettingModel()
{}

void SettingModel::init() {
    setting = new SettingModel(qApp);
}
SettingModel* SettingModel::get() {
    return setting;
}

void SettingModel::updatePos(const QPoint& pos)
{
    this->X = pos.x();
    this->Y = pos.y();
    QSqlQuery query;
    query.prepare("UPDATE Setting SET X=?,Y=?");
    query.addBindValue(X);
    query.addBindValue(Y);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
    }
}

