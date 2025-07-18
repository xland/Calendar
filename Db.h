#pragma once

#include <QObject>

class Db  : public QObject
{
	Q_OBJECT

public:
	Db(QObject *parent);
	~Db();
	static void init();
	static Db* get();
private:
	static void initDb();
};

