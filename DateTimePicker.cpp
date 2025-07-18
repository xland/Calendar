#include <QHBoxLayout>
#include <QLabel>
#include <QTimeEdit>
#include <QDateEdit>
#include <QLineEdit>

#include "DateTimePicker.h"

DateTimePicker::DateTimePicker(QWidget *parent) : QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 6, 0, 0);
    layout->setSpacing(4);
    auto label = new QLabel("日期时间：");
    label->setStyleSheet("font-size:13px;");
    layout->addWidget(label);

    QDateEdit* dateEdit = new QDateEdit(this);
    dateEdit->setCalendarPopup(true); // 显示日历选择
    dateEdit->setDate(QDate::currentDate()); // 设置当前日期
    //dateEdit->setReadOnly(true);
    ////dateEdit->setEnabled(false);
    //dateEdit->lineEdit()->setReadOnly(true);
    layout->addWidget(dateEdit);

    QTimeEdit* timeEdit = new QTimeEdit();
    timeEdit->setTime(QTime::currentTime());
    layout->addWidget(timeEdit);

    layout->addStretch();
}

DateTimePicker::~DateTimePicker()
{}

