#pragma once

#include <QWidget>
#include <QPainter>

class Flash : public QWidget
{
	Q_OBJECT

public:
	Flash(QWidget *parent = nullptr);
	~Flash();    
	static void init();
protected:
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
private:
	void timeout();
};

