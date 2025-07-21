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

ScheduleEdit::ScheduleEdit(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QWidget{background:#ffffff;}");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12,12, 12, 12);
    layout->setSpacing(6);
    repeatSelection = new RepeatSelection();
    layout->addWidget(repeatSelection);
    initDateEdit(layout);
    initTextEdit(layout);
    initBtns(layout);    
    setLayout(layout);
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
    // 创建一个下拉日期时间选择控件
    dateTimeEdit = new QDateTimeEdit();
    // 设置当前时间为默认值
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    // 启用下拉式日历
    dateTimeEdit->setCalendarPopup(true);
    dateTimeEdit->setFixedWidth(160);
    // 设置显示格式
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    dateTimeEdit->setStyleSheet(R"(QDateTimeEdit{border: 1px solid gray;border-radius: 0px;}QCalendarWidget{border: 2px solid red;})");
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

    QString btnStyle{ "QPushButton {background-color:#5D6B99; color:#ffffff; border: none; border-radius: 3px; padding: 6px;font-size:13px; }"
"QPushButton:hover { background-color: #3B4F81;}"
"QPushButton:pressed { background-color:#5D6B99;}" };

    QPushButton* addBtn = new QPushButton("增加日程");
    addBtn->setCursor(Qt::PointingHandCursor);
    addBtn->setStyleSheet(btnStyle);
    addBtn->setFixedSize(80, 30);
    btnLayout->addWidget(addBtn);

    QPushButton* editBtn = new QPushButton("修改日程");
    editBtn->setCursor(Qt::PointingHandCursor);
    editBtn->setStyleSheet(btnStyle);
    editBtn->setFixedSize(80, 30);
    btnLayout->addWidget(editBtn);

    layout->addWidget(btnBox);
    QObject::connect(editBtn, &QPushButton::clicked, this, &ScheduleEdit::save);
    QObject::connect(addBtn, &QPushButton::clicked, this, &ScheduleEdit::save);
}

void ScheduleEdit::save()
{
    QDateTime dateTime = dateTimeEdit->dateTime();
    long long timestamp = dateTime.toSecsSinceEpoch();
    QSqlQuery query;
    query.prepare("INSERT INTO Job (Id, JobInfo, StartTime, RepeatType) VALUES (?, ?, ?, ?)");
    auto uuid = QUuid::createUuid().toString().mid(1, 36);
    query.addBindValue(uuid);
    query.addBindValue(plainTextEdit->toPlainText());    // JobInfo
    query.addBindValue(timestamp); // StartTime
    query.addBindValue(repeatSelection->selectedVal);         // RepeatType
    auto flag = query.exec();
    Eventer::get()->fire("refreshData", nullptr);
}
