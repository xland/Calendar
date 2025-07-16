#pragma once
#include <Windows.h>
#include <QFont>
#include <QDate>
#include <QFontDatabase>

class Util
{
public:
	static QFont& getIconFont(const int& fontSize);
	static QFont& getTextFont(const int& fontSize);
	static HWND getWorkerW();
	static QVector<std::tuple<QDate, bool>> getOneMonthDay(const QDate& tarDate);
};

