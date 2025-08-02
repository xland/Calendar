#pragma once

#include <QObject>

class SettingModel : public QObject
{
	Q_OBJECT

public:
	SettingModel(QObject *parent);
	~SettingModel();
	static void init();
	static SettingModel* get();
	void updatePos(const QPoint& pos);
public:
	int X, Y, AlertBefore;
};

