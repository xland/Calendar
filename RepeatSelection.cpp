#include <QHBoxLayout>
#include <QLabel>
#include "RepeatSelection.h"
#include "RepeatSelectionBtn.h"
#include "BtnBase.h"
#include "Util.h"

RepeatSelection::RepeatSelection(QWidget *parent) : QWidget(parent)
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
    auto rsb4 = new RepeatSelectionBtn(4);
    connect(rsb4, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb4);
    auto rsb5 = new RepeatSelectionBtn(5);
    connect(rsb5, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb5);
    auto rsb6 = new RepeatSelectionBtn(6);
    connect(rsb6, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    layout->addWidget(rsb6);
    layout->addStretch();
}

RepeatSelection::~RepeatSelection()
{

}

void RepeatSelection::selectionChanged()
{
    auto btn = (RepeatSelectionBtn*)sender();
    selectedVal = btn->val;
    update();
}

