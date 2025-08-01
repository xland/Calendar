#pragma once
#include <QVBoxLayout>
#include <QWidget>
#include <QPainter>
#include "MenuItem.h"

class Menu : public QWidget
{
	Q_OBJECT

public:
	Menu(QWidget *parent = nullptr);
	~Menu();
signals:
	void menuChanged(QString menuName);
private:
	void menuClick();
	void initMenus(QVBoxLayout* layout);
private:
	QList<MenuItem*> menus;
};

