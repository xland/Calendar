#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QSqlQuery>
#include <QUuid>
#include <QTimeEdit>

#include "DateTimePicker.h"
#include "ScheduleEdit.h"
#include "Util.h"
#include "RepeatSelection.h"

ScheduleEdit::ScheduleEdit(QWidget *parent) : QWidget(parent)
{
    setObjectName("scheduleEdit");
    setStyleSheet("QWidget{background:#ffffff;}");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12,12, 12, 12);
    layout->setSpacing(6);
    auto rs = new RepeatSelection();
    layout->addWidget(rs);

    auto dateTimePicker = new DateTimePicker();
    layout->addWidget(dateTimePicker);


    auto label = new QLabel("日程内容：");
    label->setFixedHeight(28);
    label->setStyleSheet("font-size:13px;");
    layout->addWidget(label);
    QPlainTextEdit* plainTextEdit = new QPlainTextEdit(this);
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(26, QTextBlockFormat::FixedHeight);
    QTextCursor cursor = plainTextEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(blockFormat);
    cursor.clearSelection();
    plainTextEdit->setTextCursor(cursor);
    plainTextEdit->document()->setDefaultFont(Util::getTextFont(14));
    plainTextEdit->setStyleSheet("line-height:36px;");
    layout->addWidget(plainTextEdit);

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
    setLayout(layout);
}

ScheduleEdit::~ScheduleEdit()
{

}

void ScheduleEdit::save()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Job (Id, JobInfo, StartTime, EndTime, RepeatType) VALUES (?, ?, ?, ?, ?)");
    auto uuid = QUuid::createUuid().toString().mid(1, 36);
    query.addBindValue(uuid);
    query.addBindValue("Sample Job");    // JobInfo
    query.addBindValue(123); // StartTime
    query.addBindValue(456); // EndTime
    query.addBindValue(1);         // RepeatType
    auto flag = query.exec();

}

