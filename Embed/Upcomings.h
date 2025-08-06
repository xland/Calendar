#pragma once

#include <QTimer>
#include <QWidget>
#include <QList>

class UpcomingItem;
class Upcomings : public QWidget
{
	Q_OBJECT

public:
	Upcomings(QWidget *parent = nullptr);
	~Upcomings();
private:
	void timeout();
	void initChildren();
	void needChange();
	void removeTimer();
private:
	QTimer* timer;
	QList<UpcomingItem*> upcomingItems;
};

