#include <QHBoxLayout>
#include <QLabel>
#include "RepeatSelection.h"
#include "RepeatSelectionBtn.h"
#include "BtnBase.h"
#include "Util.h"

RepeatSelection::RepeatSelection(const int& val, QWidget *parent) : QWidget(parent), selectedVal{val}
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(4);
    auto label = new QLabel("重复类型：");
    label->setStyleSheet("font-size:13px;");
    layout->addWidget(label);
    auto rsb = new RepeatSelectionBtn(0);
    connect(rsb, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb);
    auto rsb1 = new RepeatSelectionBtn(1);
    connect(rsb1, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb1);
    auto rsb2 = new RepeatSelectionBtn(2);
    connect(rsb2, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb2);
    auto rsb3 = new RepeatSelectionBtn(3);
    connect(rsb3, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb3);
    rsb4 = new RepeatSelectionBtn(4);
    connect(rsb4, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb4);
    rsb5 = new RepeatSelectionBtn(5);
    connect(rsb5, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb5);
    rsb6 = new RepeatSelectionBtn(6);
    connect(rsb6, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb6);
    layout->addStretch();
}

RepeatSelection::~RepeatSelection()
{

}

void RepeatSelection::changeDate(const QDate& date)
{
    QString days[] = { "一", "二", "三", "四","五","六","日" };
    rsb4->labelStr = QString("每周%1").arg(days[date.dayOfWeek() - 1]);
    rsb5->labelStr = QString("每月第%1天").arg(date.day());
    rsb6->labelStr = QString("每年%1月%2日").arg(QString::number(date.month()).trimmed(), QString::number(date.day()).trimmed());
}

void RepeatSelection::selectionChanged()
{
    auto btn = (RepeatSelectionBtn*)sender();
    selectedVal = btn->val;
    update();
}

