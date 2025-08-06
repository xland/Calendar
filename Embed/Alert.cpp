#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

#include "Alert.h"
#include "../Util.h"
#include "../Data/ScheduleModel.h"
#include "../Data/Schedules.h"

Alert::Alert(const QString& modelId, QWidget* parent) : QDialog(parent),Id{modelId}
{ 
	setWindowIcon(QIcon(":/logo.ico"));
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	resize(500, 200);
	setWindowTitle("日程提醒");

	model = new ScheduleModel(modelId, this);


	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(12, 12, 12, 12);
	layout->setSpacing(0);

	auto plainTextEdit = new QPlainTextEdit(this);
	plainTextEdit->setPlainText(model->Schedule);
	plainTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QTextBlockFormat blockFormat;
	blockFormat.setLineHeight(26, QTextBlockFormat::FixedHeight);
	QTextCursor cursor = plainTextEdit->textCursor();
	cursor.select(QTextCursor::Document);
	cursor.mergeBlockFormat(blockFormat);
	cursor.clearSelection();
	plainTextEdit->setTextCursor(cursor);
	plainTextEdit->document()->setDefaultFont(Util::getTextFont(14));
	layout->addWidget(plainTextEdit);

	layout->addSpacing(12);

	{
		auto box = new QWidget();
		auto l = new QHBoxLayout(box);
		l->setContentsMargins(0, 0, 0, 0);
		l->setSpacing(0);

		remainTimeText = new QLabel();
		l->addWidget(remainTimeText);
		l->addSpacing(12); //用于控制窗口最小尺寸

		l->addStretch();
		QString btnStyle{ "QPushButton{background-color:%1;color:#ffffff;border:none;border-radius:3px;padding:6px;font-size:13px;}"
"QPushButton:hover{background-color:%2;} QPushButton:pressed{background-color:%1;}" };
		auto btn = new QPushButton("知道了，不再提醒");
		btn->setCursor(Qt::PointingHandCursor);
		btn->setStyleSheet(btnStyle.arg("#5D6B99").arg("#3B4F81"));
		btn->setFixedSize(136, 30);
		l->addWidget(btn);

		l->addSpacing(12);
		auto btn2 = new QPushButton("取消");
		btn2->setCursor(Qt::PointingHandCursor);
		btn2->setStyleSheet(btnStyle.arg("#5D6B99").arg("#3B4F81"));
		btn2->setFixedSize(58, 30);
		l->addWidget(btn2);

		connect(btn, &QPushButton::clicked, this, &Alert::okBtnClick);
		connect(btn2, &QPushButton::clicked, this, &Alert::close);
		layout->addWidget(box);
	}
	timeout();
	connect(Schedules::get(), &Schedules::scheduleChanged, this, &Alert::modelChange);
}

Alert::~Alert()
{
}

void Alert::modelChange() {
	removeTimer();
	delete model;
	model = new ScheduleModel(Id, this);
	timeout();
}

void Alert::okBtnClick()
{
	model->IsExpire = true;
	model->setNextTime();
	model->update();
	close();
}
void Alert::removeTimer() {
	if (timer) {
		timer->stop();
		delete timer;
		timer = nullptr;
	}
}
void Alert::timeout() {
	auto timespan = model->UpcomingTime - QDateTime::currentDateTime().toSecsSinceEpoch();
	auto str = Util::getTimeStr(timespan);
	remainTimeText->setText(QString("日程到期时间：%1").arg(str));
	if (timespan <= 0) {
		removeTimer();
	}
	else {
		if (!timer) {
			timer = new QTimer(this);
			connect(timer, &QTimer::timeout, this, &Alert::timeout);
		}
		if (str.endsWith("秒")) {
			timer->start(1000);
		}
		else {
			timer->start(60000);
		}
	}
}
