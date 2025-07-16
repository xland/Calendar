#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include "ScheduleEdit.h"

ScheduleEdit::ScheduleEdit(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    QTextEdit* textEdit = new QTextEdit();
    textEdit->setPlaceholderText("请输入多行文本...");
    textEdit->setMinimumHeight(150);
    layout->addWidget(textEdit);

    auto btnBox = new QWidget();
    auto btnLayout = new QHBoxLayout(btnBox);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->addStretch();
    QPushButton* button = new QPushButton("删除");
    btnLayout->addWidget(button);
    QPushButton* clearButton = new QPushButton("保存");
    btnLayout->addWidget(clearButton);

    layout->addWidget(btnBox);
    QObject::connect(clearButton, &QPushButton::clicked, textEdit, &QTextEdit::clear);
    setLayout(layout);
}

ScheduleEdit::~ScheduleEdit()
{

}

