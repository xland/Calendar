#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include <QComboBox>
#include <QLabel>
#include <QSqlQuery>
#include <QUuid>
#include <QTimeEdit>

#include "ScheduleEdit.h"
#include "Util.h"
#include "Eventer.h"
#include "../Data/Schedules.h"
#include "RepeatSelectionBtn.h"
#include "DialogList.h"

ScheduleEdit::ScheduleEdit(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QWidget{background:#ffffff;}");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12,12, 12, 12);
    layout->setSpacing(6);
    repeatSelection = new RepeatSelection(0);
    layout->addWidget(repeatSelection);
    initDateEdit(layout);
    initTextEdit(layout);
    initBtns(layout);    
    setLayout(layout);
    connect(Eventer::get(), &Eventer::schedulesChange, this, &ScheduleEdit::updateData);
    updateData();
}

ScheduleEdit::~ScheduleEdit()
{

}

void ScheduleEdit::initDateEdit(QVBoxLayout* layout)
{
    auto dateTimePicker = new QWidget();
    auto dateTimeLayout = new QHBoxLayout(dateTimePicker);
    dateTimeLayout->setContentsMargins(0, 6, 0, 0);
    dateTimeLayout->setSpacing(4);
    auto label = new QLabel("提醒时间：");
    label->setStyleSheet("font-size:13px;");
    dateTimeLayout->addWidget(label);
    dateTimeEdit = new QDateTimeEdit();
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setFixedWidth(160);
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    dateTimeEdit->setStyleSheet(R"(QDateTimeEdit{border:1px solid gray;border-radius:0px;}QCalendarWidget{border:2px solid red;})");
    dateTimeLayout->addWidget(dateTimeEdit);
    dateTimeLayout->addStretch();
    layout->addWidget(dateTimePicker);
}

void ScheduleEdit::initTextEdit(QVBoxLayout* layout)
{
    auto label = new QLabel("日程内容：");
    label->setFixedHeight(28);
    label->setStyleSheet("font-size:13px;");
    layout->addWidget(label);
    plainTextEdit = new QPlainTextEdit(this);
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

void ScheduleEdit::initBtns(QVBoxLayout* layout)
{
    auto btnBox = new QWidget();
    auto btnLayout = new QHBoxLayout(btnBox);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(12);
    btnLayout->addStretch();

    QString btnStyle{"QPushButton {background-color:#5D6B99; color:#ffffff; border: none; border-radius: 3px; padding: 6px;font-size:13px; }"
"QPushButton:hover { background-color: #3B4F81;}"
"QPushButton:pressed { background-color:#5D6B99;}"};

    btn = new QPushButton("增加日程");
    btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(btnStyle);
    btn->setFixedSize(80, 30);
    btnLayout->addWidget(btn);

    layout->addWidget(btnBox);
    QObject::connect(btn, &QPushButton::clicked, this, &ScheduleEdit::save);
}

void ScheduleEdit::updateData()
{
    //data = Schedules::get()->getSelectedData();
    //if (data) {
    //    plainTextEdit->setPlainText(data->JobInfo);
    //    plainTextEdit->selectAll();
    //    plainTextEdit->setFocus();
    //    btn->setText("修改日程");
    //}
    //else {
    //    auto p = (DialogList*)topLevelWidget();
    //    QDateTime dateTime(p->curDay, QTime::currentTime());
    //    long long timestamp = dateTime.toSecsSinceEpoch();
    //    data = new ScheduleModel("日程内容......", timestamp, 0, Schedules::get());
    //    plainTextEdit->setPlainText(data->JobInfo);
    //    plainTextEdit->selectAll();
    //    plainTextEdit->setFocus();
    //    btn->setText("增加日程");
    //}   
    //QDateTime restoredDateTime = QDateTime::fromSecsSinceEpoch(data->StartTime);
    //dateTimeEdit->setDateTime(restoredDateTime);
    //repeatSelection->selectedVal = data->RepeatType;
    //auto btns = repeatSelection->findChildren<RepeatSelectionBtn*>();
    //auto day = restoredDateTime.date();
    //QString days[] = {"一", "二", "三", "四","五","六","日"};
    //btns[3]->labelStr = QString("每周%1").arg(days[day.dayOfWeek()-1]);
    //btns[4]->labelStr = QString("每月第%1天").arg(day.day());
    //btns[5]->labelStr = QString("每年%1月%2日").arg(QString::number(day.month()).trimmed(), QString::number(day.day()).trimmed());
    //repeatSelection->update();
}

void ScheduleEdit::save()
{
    //QDateTime dateTime = dateTimeEdit->dateTime();
    //long long timestamp = dateTime.toSecsSinceEpoch();
    //data->JobInfo = plainTextEdit->toPlainText();
    //data->StartTime = timestamp;
    //data->RepeatType = repeatSelection->selectedVal;
    //if (data->isNew) {
    //    Schedules::get()->addData(data);
    //}
    //else {
    //    Schedules::get()->editData(data);
    //}
    
}
