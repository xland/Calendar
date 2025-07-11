#pragma once

#include <QWidget>

class TipInfo : public QWidget
{
	Q_OBJECT

public:
	~TipInfo();
	static void init();
	static TipInfo* get();
	void showInfo(const QPoint& pos);
	void setText(const QString& text);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	TipInfo(QWidget* parent = nullptr);
	QString text;
};
