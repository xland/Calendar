#pragma once
#include <QHBoxLayout>
#include <QWidget>

class DialogSetting : public QWidget
{
	Q_OBJECT

public:
	DialogSetting(QWidget *parent = nullptr);
	~DialogSetting();

private:
	void menuChanged(QString menuText);
};

