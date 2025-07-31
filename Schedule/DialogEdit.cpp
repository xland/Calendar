#include <QHBoxLayout>
#include <QLabel>

#include "DialogEdit.h"
#include "RepeatSelectionBtn.h"
#include "../Data/Schedules.h"
#include "../Util.h"

DialogEdit::DialogEdit(const QString& id,const QDate& date,QWidget *parent) : QWidget(parent),date{date}
{
	setWindowIcon(QIcon(":/logo.ico"));
	setObjectName("DialogEdit");
	setStyleSheet("#DialogEdit{background:#ffffff;}");
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(600, 500);
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(12, 12, 12, 12);
	layout->setSpacing(6);

    initData(id);
    setWindowTitle(title);
	repeatSelection = new RepeatSelection(data->RepeatType);
    repeatSelection->changeDate(QDateTime::fromSecsSinceEpoch(data->FirstTime).date());
	layout->addWidget(repeatSelection);
	initDateEdit(layout);
	initTextEdit(layout);
	initBtns(layout);
	setLayout(layout);
}

DialogEdit::~DialogEdit()
{

}

void DialogEdit::showEvent(QShowEvent* event)
{
    plainTextEdit->setFocus();
}

void DialogEdit::initDateEdit(QVBoxLayout* layout)
{
    auto dateTimePicker = new QWidget();
    auto dateTimeLayout = new QHBoxLayout(dateTimePicker);
    dateTimeLayout->setContentsMargins(0, 6, 0, 0);
    dateTimeLayout->setSpacing(4);
    auto label = new QLabel("提醒时间：");
    label->setStyleSheet("font-size:13px;");
    dateTimeLayout->addWidget(label);
    dateTimeEdit = new QDateTimeEdit();
    dateTimeEdit->setDateTime(QDateTime::fromSecsSinceEpoch(data->FirstTime));
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setFixedWidth(160);
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    dateTimeEdit->setStyleSheet(R"(QDateTimeEdit{border:1px solid gray;border-radius:0px;}QCalendarWidget{border:2px solid red;})");
    dateTimeLayout->addWidget(dateTimeEdit);
    dateTimeLayout->addStretch();
    layout->addWidget(dateTimePicker);
}

void DialogEdit::initTextEdit(QVBoxLayout* layout)
{
    auto label = new QLabel("日程内容：");
    label->setFixedHeight(28);
    label->setStyleSheet("font-size:13px;");
    layout->addWidget(label);
    plainTextEdit = new QPlainTextEdit(this);
    plainTextEdit->setPlainText(data->Schedule);
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(26, QTextBlockFormat::FixedHeight);
    QTextCursor cursor = plainTextEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(blockFormat);
    cursor.clearSelection();
    plainTextEdit->setTextCursor(cursor);
    plainTextEdit->document()->setDefaultFont(Util::getTextFont(14));
    plainTextEdit->setStyleSheet("line-height:36px;padding:5px;");
    layout->addWidget(plainTextEdit);
}

void DialogEdit::initBtns(QVBoxLayout* layout)
{
    auto btnBox = new QWidget();
    auto btnLayout = new QHBoxLayout(btnBox);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->addStretch();
    QString btnStyle{ "QPushButton{background-color:#5D6B99; color:#ffffff; border: none; border-radius: 3px; padding: 6px;font-size:13px; }"
"QPushButton:hover{background-color: #3B4F81;} QPushButton:pressed { background-color:#5D6B99;}" };
    btn = new QPushButton(title);
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(btnStyle);
    btn->setFixedSize(80, 30);
    btnLayout->addWidget(btn);

    layout->addWidget(btnBox);
    QObject::connect(btn, &QPushButton::clicked, this, &DialogEdit::btnClick);
}

void DialogEdit::initData(const QString& id)
{
    if (id.isEmpty()) {
        title = "增加日程";
        data = new ScheduleModel(Schedules::get());
        data->FirstTime = QDateTime(date, QTime(9, 0, 0)).toSecsSinceEpoch();
        data->Schedule = "日程内容...";
    }
    else {
        title = "修改日程";
        data = Schedules::get()->getData(id);
    }
}

void DialogEdit::btnClick()
{
    QDateTime dt = dateTimeEdit->dateTime();
    QDateTime curDt = QDateTime::currentDateTime();
    data->Schedule = plainTextEdit->toPlainText();
    data->RepeatType = repeatSelection->selectedVal;
    data->CreateTime = curDt.toSecsSinceEpoch();
    data->FirstTime = dt.toSecsSinceEpoch();
    data->UpcomingTime = data->FirstTime;
    Schedules::get()->setUpcomingTime(data);
    if (data->RepeatType == 1) {
        data->IsExpire = data->FirstTime < data->CreateTime;
    }
    if (title == "增加日程") {
        Schedules::get()->addData(data);
    }
    else {
        Schedules::get()->editData(data);
    }
    close();
}
