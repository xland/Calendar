#pragma once
#include <QSpinBox>
#include <QWidget>

class Setting : public QWidget
{
	Q_OBJECT

public:
	Setting(QWidget *parent = nullptr);
	~Setting();

private:
	void saveBtnClick();
	QSpinBox* input;
};

