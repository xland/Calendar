#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include "ScheduleBox.h"
#include "ScheduleList.h"
#include "ScheduleTab.h"
#include "ScheduleSearch.h"

ScheduleBox::ScheduleBox(QWidget *parent) : QWidget(parent)
{
	setMinimumWidth(180);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
    auto tabs = new ScheduleTab();    
    layout->addWidget(tabs);
    auto searchBox = new ScheduleSearch();
    layout->addWidget(searchBox);
    auto sc = new ScheduleList(this);
    layout->addWidget(sc);
}

ScheduleBox::~ScheduleBox()
{

}

