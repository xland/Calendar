#include <QHBoxLayout>
#include <QLabel>
#include "RepeatSelection.h"
#include "RepeatSelectionBtn.h"
#include "BtnBase.h"
#include "Util.h"

RepeatSelection::RepeatSelection(QWidget *parent) : QWidget(parent)
{
    auto selectLayout = new QHBoxLayout(this);
    selectLayout->setContentsMargins(0, 0, 0, 0);
    selectLayout->setSpacing(4);
    auto label1 = new QLabel("重复类型：");
    label1->setStyleSheet("font-size:13px;");
    selectLayout->addWidget(label1);
    auto rsb = new RepeatSelectionBtn(0);
    connect(rsb, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    selectLayout->addWidget(rsb);
    auto rsb1 = new RepeatSelectionBtn(1);
    connect(rsb1, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    selectLayout->addWidget(rsb1);
    auto rsb2 = new RepeatSelectionBtn(2);
    connect(rsb2, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    selectLayout->addWidget(rsb2);
    auto rsb3 = new RepeatSelectionBtn(3);
    connect(rsb3, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    selectLayout->addWidget(rsb3);
    auto rsb4 = new RepeatSelectionBtn(4);
    connect(rsb4, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    selectLayout->addWidget(rsb4);
    auto rsb5 = new RepeatSelectionBtn(5);
    connect(rsb5, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    selectLayout->addWidget(rsb5);
    auto rsb6 = new RepeatSelectionBtn(6);
    connect(rsb6, &BtnBase::click, this, &RepeatSelection::selectionChanged);
    selectLayout->addWidget(rsb6);
    selectLayout->addStretch();
}

RepeatSelection::~RepeatSelection()
{

}

void RepeatSelection::selectionChanged()
{
    auto btn = (RepeatSelectionBtn*)sender();
}

