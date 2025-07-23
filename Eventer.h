#pragma once

#include <QObject>

class Eventer  : public QObject
{
	Q_OBJECT

public:
	Eventer(QObject *parent);
	~Eventer();
	static void init();
	static Eventer* get();
	static void fire(const QString& eventName, const QObject* data);
signals:
	void globalEvent(const QString& eventName, const QObject* data);
};

