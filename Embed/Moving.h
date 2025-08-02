#pragma once
#include <QPainter>
#include <QWidget>

class Moving : public QWidget
{
	Q_OBJECT

public:
	Moving(QWidget *parent = nullptr);
	~Moving();
	void resetPos();
protected:
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
private:
};

