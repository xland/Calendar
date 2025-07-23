#include <qApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>

#include "Db.h"

Db* db;

Db::Db(QObject *parent) : QObject(parent)
{

}

Db::~Db()
{}

void Db::init() {
    initDb();
	db = new Db(qApp);
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
        flag = query.exec("CREATE TABLE Job(Id VARCHAR2(36) NOT NULL ON CONFLICT FAIL UNIQUE ON CONFLICT FAIL,JobInfo TEXT,RepeatType INT,StartTime BIGINT);");
        flag = query.exec("CREATE INDEX JobInfo_Index ON Job(JobInfo);");
        flag = query.exec("CREATE TABLE Setting(ViewDefault INT DEFAULT 0, ViewVal Int, LangDefault INT DEFAULT 0, SkinDefault INT DEFAULT 0, AlertBefore INT);");
        flag = query.exec("INSERT INTO Setting(ViewDefault, ViewVal, LangDefault, SkinDefault, AlertBefore) VALUES (0, 0, 0, 0, 5);");
    }
}

