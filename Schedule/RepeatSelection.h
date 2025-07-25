#pragma once
#include <QPainter>
#include <QWidget>

class RepeatSelectionBtn;
class RepeatSelection : public QWidget
{
	Q_OBJECT

public:
	RepeatSelection(const int& val, QWidget *parent = nullptr);
	~RepeatSelection();
	int selectedVal{0};
	void changeDate(const QDate& date);
protected:
private:
	void selectionChanged();
	RepeatSelectionBtn* rsb4;
	RepeatSelectionBtn* rsb5;
	RepeatSelectionBtn* rsb6;
};

