#include <qApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>

#include "Db.h"
#include "Schedules.h"
#include "TickTock.h"
#include "Dates.h"
#include "SettingModel.h"

Db* db;

Db::Db(QObject *parent) : QObject(parent)
{

}

Db::~Db()
{}

void Db::init() {
    initDb();
	db = new Db(qApp);
    Dates::init();
    Schedules::init();
    TickTock::init();
    SettingModel::init();
}
Db* Db::get() {
	return db;
}

void Db::initDb()
{
    QApplication::setApplicationName("Calendar");
    QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!appDataDir.isEmpty()) {
        QDir dir;
        if (!dir.exists(appDataDir)) {
            bool created = dir.mkpath(appDataDir); // 创建多级目录（包括父目录）
            if (created) {
                qDebug() << "AppData 目录已创建：" << appDataDir;
            }
            else {
                qDebug() << "无法创建 AppData 目录：" << appDataDir;
            }
        }
        else {
            qDebug() << "AppData 目录已存在：" << appDataDir;
        }
    }
    else {
        qDebug() << "无法获取 AppData 目录路径。";
    }
    auto dbPath = QDir::cleanPath(appDataDir + QDir::separator() + "db.db");
    auto dbExists = QFile::exists(dbPath);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "无法打开数据库";
        return;
    }
    if (!dbExists) {
        QSqlQuery query;
        auto flag = query.exec("PRAGMA journal_mode = WAL;");
        flag = query.exec("CREATE TABLE Schedule(Id VARCHAR2(36) NOT NULL ON CONFLICT FAIL UNIQUE ON CONFLICT FAIL,Schedule TEXT,IsExpire INT,RepeatType INT,CreateTime BIGINT,FirstTime BIGINT,UpcomingTime BIGINT,Year INT,Month INT,Day INT,Time INT);");
        flag = query.exec("CREATE INDEX Schedule_Index ON Job(Schedule);");
        flag = query.exec("CREATE TABLE Setting(X INT,Y INT,AlertBefore INT);");
        flag = query.exec("INSERT INTO Setting(X,Y,AlertBefore) VALUES (999999,999999,300);");
    }
}

