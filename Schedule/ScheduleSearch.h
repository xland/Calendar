#pragma once
#include <QLineEdit>
#include <QPainter>
#include <QWidget>

class ScheduleSearch : public QWidget
{
	Q_OBJECT

public:
	ScheduleSearch(QWidget *parent = nullptr);
	~ScheduleSearch();
protected:
	void resizeEvent(QResizeEvent* event) override;	
	void paintEvent(QPaintEvent* event) override;
private:
	QLineEdit* input;
	int h{ 32 };
};

