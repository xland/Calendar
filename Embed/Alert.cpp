#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

#include "../Util.h"
#include "Alert.h"
#include "../Data/ScheduleModel.h"

Alert::Alert(const QString& modelId, QWidget* parent) : QWidget(parent)
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
		QString btnStyle{ "QPushButton{background-color:#5D6B99;color:#ffffff;border:none;border-radius:3px;padding:6px;font-size:13px;}"
"QPushButton:hover{background-color:#3B4F81;} QPushButton:pressed{background-color:#5D6B99;}" };
		auto btn = new QPushButton("知道了");
		btn->setCursor(Qt::PointingHandCursor);
		btn->setStyleSheet(btnStyle);
		btn->setFixedSize(80, 30);
		l->addWidget(btn);

		connect(btn, &QPushButton::clicked, this, &Alert::okBtnClick);
		layout->addWidget(box);
	}
	timeout();
}

Alert::~Alert()
{
}

void Alert::okBtnClick()
{
	model->IsExpire = true;
	model->setNextTime();
	model->update();
	close();
}
void Alert::timeout() {
	auto timespan = model->UpcomingTime - QDateTime::currentDateTime().toSecsSinceEpoch();
	auto str = Util::getTimeStr(timespan);
	remainTimeText->setText(str);
	if (timespan <= 0) {
		if (timer) {
			timer->stop();
			timer->deleteLater();
		}
	}
	else if(!timer) {
		timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &Alert::timeout);
		timer->start(1000);
	}
}
