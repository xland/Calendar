#pragma once

#include <QWidget>

class BtnBase : public QWidget
{
	Q_OBJECT

public:
	BtnBase(QWidget *parent = nullptr);
	~BtnBase();
public:
	virtual void enterEvent(QEnterEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	bool isHover{ false };
signals:
	void click();
	void enter();
	void leave();
protected:
private:
};
