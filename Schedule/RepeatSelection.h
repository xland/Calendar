#pragma once
#include <QPainter>
#include <QWidget>

class RepeatSelection : public QWidget
{
	Q_OBJECT

public:
	RepeatSelection(QWidget *parent = nullptr);
	~RepeatSelection();
	int selectedVal{0};
protected:
private:
	void selectionChanged();
};

