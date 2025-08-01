#pragma once

#include <QWidget>
#include <QPainter>
#include "../BtnBase.h"

class MenuItem : public BtnBase
{
	Q_OBJECT

public:
	MenuItem(const QString& text, bool isSelected=false, QWidget *parent = nullptr);
	~MenuItem();
	bool isSelected{false};
	QString text;
protected:
	void paintEvent(QPaintEvent* event) override;
private:
};

