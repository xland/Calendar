#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <QList>

#include "Util.h"

QFont& Util::getIconFont(const int& fontSize)
{
    static QFont font = []() {
        int fontId = QFontDatabase::addApplicationFont(":/iconfont.ttf");
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont iconFont(fontName);
        iconFont.setStyleStrategy(QFont::PreferAntialias);
        iconFont.setHintingPreference(QFont::PreferNoHinting);
        return iconFont;
    }();
    font.setPixelSize(fontSize);
    return font;
}

QFont& Util::getTextFont(const int& fontSize)
{
    static QFont font = []() {
        QFont font("Microsoft YaHei");
        font.setStyleStrategy(QFont::PreferAntialias);
        font.setHintingPreference(QFont::PreferNoHinting);
        return font;
        }();
    font.setPixelSize(fontSize);
    return font;
}


HWND Util::getWorkerW()
{
    static HWND workerW;
    if (!workerW) {
        HWND progman = FindWindow(L"Progman", NULL);
        SendMessage(progman, 0x052C, 0xD, 0);
        SendMessage(progman, 0x052C, 0xD, 1);
        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            HWND defView = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL);
            if (defView != NULL) {
                auto tar = (HWND*)lParam;
                *tar = FindWindowEx(NULL, hwnd, L"WorkerW", NULL);
            }
            return TRUE;
            }, (LPARAM)&workerW);
    }
    return workerW;
}


QVector<std::tuple<QDate, bool>> Util::getOneMonthDay(const QDate& tarDate)
{
    QVector<std::tuple<QDate, bool>> result;

    int year = tarDate.year();
    int month = tarDate.month(); // 1~12

    // 上个月最后一天
    QDate preMonthLastDay = QDate(year, month, 1).addDays(-1);
    int weekIndex = preMonthLastDay.dayOfWeek(); // 1 = Monday, 7 = Sunday
    if (weekIndex < 7) {
        int startDay = preMonthLastDay.day() - weekIndex + 1;
        for (int i = startDay; i <= preMonthLastDay.day(); ++i) {
            result.append({ QDate(preMonthLastDay.year(), preMonthLastDay.month(), i), false });
        }
    }

    // 当前月天数
    QDate curMonthFirstDay(year, month, 1);
    QDate curMonthLastDay = curMonthFirstDay.addMonths(1).addDays(-1);
    for (int i = 1; i <= curMonthLastDay.day(); ++i) {
        result.append({ QDate(year, month, i), true });
    }

    // 下个月补足剩余天数
    int lastDayCount = 42 - result.size();
    if (lastDayCount > 0) {
        QDate nextMonthFirstDay = curMonthFirstDay.addMonths(1);
        for (int i = 1; i <= lastDayCount; ++i) {
            result.append({ QDate(nextMonthFirstDay.year(), nextMonthFirstDay.month(), i), false });
        }
    }

    return result;
}

QString Util::getTimeStr(const qint64 timespan)
{
    qint64 days = timespan / 86400;
    if (days > 0) return QString("%1天").arg(days);
    qint64 hours = timespan / 3600;
    if (hours > 0) return QString("%1小时").arg(hours);
    qint64 minutes = timespan / 60;
    if (minutes > 0) return QString("%1分钟%2秒").arg(minutes).arg(timespan % 60, 2, 10, QChar('0'));
    if (timespan > 0) return QString("%1秒").arg(timespan, 2, 10, QChar('0'));
    else return QString("已发生");
}
