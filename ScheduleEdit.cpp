#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLabel>

#include "ScheduleEdit.h"
#include "Util.h"
#include "RepeatSelection.h"

ScheduleEdit::ScheduleEdit(QWidget *parent) : QWidget(parent)
{
    setObjectName("scheduleEdit");
    setStyleSheet("QWidget{background:#ffffff;}");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 8, 8, 8);
    layout->setSpacing(6);

    auto rs = new RepeatSelection();
    layout->addWidget(rs);

//    QComboBox* comboBox = new QComboBox();
//    comboBox->addItem("不重复");
//    comboBox->addItem("每天");
//    comboBox->addItem("每个工作日");
//    comboBox->addItem("每周一");
//    comboBox->addItem("每月第12天");
//    comboBox->addItem("每年12月12日");
//    comboBox->setCurrentIndex(0);
//    comboBox->setStyleSheet("QComboBox{color:#666666;font-size:14px;padding: 1px 15px 1px 3px;border:1px solid rgba(228,228,228,1);border-radius:5px 5px 0px 0px;}"
//"QComboBox::drop-down{subcontrol-origin:padding;subcontrol-position:top right;width:15px;border:none;}"
//"QComboBox QAbstractItemView::item{height:36px;color:#666666;padding-left:9px;background-color:#FFFFFF;}"
//"QComboBox QAbstractItemView::item:hover{background-color:#409CE1; color:#ffffff; }"
//"QComboBox QAbstractItemView::item:selected{background-color:#409CE1; color:#ffffff; }");
//    selectLayout->addWidget(comboBox);
//    selectLayout->addStretch();
//    layout->addWidget(selectBox);



    QPlainTextEdit* plainTextEdit = new QPlainTextEdit(this);
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(26, QTextBlockFormat::FixedHeight);
    QTextCursor cursor = plainTextEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(blockFormat);
    cursor.clearSelection();
    plainTextEdit->setTextCursor(cursor);
    plainTextEdit->document()->setDefaultFont(Util::getTextFont(14));
    plainTextEdit->setPlaceholderText("请输入日程内容");
    plainTextEdit->setStyleSheet("line-height:36px;");
    layout->addWidget(plainTextEdit);

    auto btnBox = new QWidget();
    btnBox->setStyleSheet("background:#ffffff;");
    auto btnLayout = new QHBoxLayout(btnBox);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->addStretch();
    QPushButton* addButton = new QPushButton("保存");
    addButton->setFixedSize(80, 30);
    btnLayout->addWidget(addButton);

    layout->addWidget(btnBox);
    QObject::connect(addButton, &QPushButton::clicked, this, &ScheduleEdit::save);
    setLayout(layout);
}

ScheduleEdit::~ScheduleEdit()
{

}

void ScheduleEdit::save()
{
}

