#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "Setting.h"
#include "../Data/SettingModel.h"

Setting::Setting(QWidget *parent) : QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(255, 255, 255));
	setPalette(pal);
	setAutoFillBackground(true);
	setStyleSheet("QLabel{font-size:13px;}"
		"QSpinBox { border:1px solid gray; }"
		"QSpinBox::up-button {subcontrol-position: top right; }"
		"QSpinBox::down-button {subcontrol-position: bottom right; }");
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(12, 12, 12, 12);
	layout->setSpacing(12);
	auto s = SettingModel::get();
	{
		auto box = new QWidget();
		auto l = new QHBoxLayout(box);
		l->setContentsMargins(0, 0, 0, 0);
		l->setSpacing(0);
		QLabel* label = new QLabel("提前：");
		l->addWidget(label);
		inputAlertBefore = new QSpinBox();
		inputAlertBefore->setRange(0, 120);
		inputAlertBefore->setSingleStep(1);
		inputAlertBefore->setValue(s->AlertBefore); 
		l->addWidget(inputAlertBefore);
		l->addSpacing(8);
		l->addWidget(new QLabel("分钟提醒日程"));
		l->addStretch();
		layout->addWidget(box);
	}

	{
		auto box = new QWidget();
		auto l = new QHBoxLayout(box);
		l->setContentsMargins(0, 0, 0, 0);
		l->setSpacing(0);
		QLabel* label = new QLabel("桌面窗口底部显示：");
		l->addWidget(label);
		inputUpcomingNum = new QSpinBox();
		inputUpcomingNum->setRange(0, 120);
		inputUpcomingNum->setSingleStep(1);
		inputUpcomingNum->setValue(s->UpcomingNum);
		l->addWidget(inputUpcomingNum);
		l->addSpacing(8);
		l->addWidget(new QLabel("条日程"));
		l->addStretch();
		layout->addWidget(box);
	}

	{
		auto box = new QWidget();
		auto l = new QHBoxLayout(box);
		l->setContentsMargins(0, 0, 0, 0);
		l->setSpacing(0);
		l->addStretch();
		QString btnStyle{"QPushButton{background-color:#5D6B99;color:#ffffff;border:none;border-radius:3px;padding:6px;font-size:13px;}"
"QPushButton:hover{background-color:#3B4F81;} QPushButton:pressed{background-color:#5D6B99;}" };
		auto btn = new QPushButton("更新设置");
		btn->setCursor(Qt::PointingHandCursor);
		btn->setStyleSheet(btnStyle);
		btn->setFixedSize(80, 30);
		l->addWidget(btn);
		layout->addWidget(box);
		connect(btn, &QPushButton::clicked, this, &Setting::saveBtnClick);
	}
	layout->addStretch();
}

Setting::~Setting()
{

}

void Setting::saveBtnClick()
{
	auto s = SettingModel::get();
	s->AlertBefore = inputAlertBefore->value();
	s->UpcomingNum = inputUpcomingNum->value();
	s->updateSetting();
}

