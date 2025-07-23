#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include "ScheduleBox.h"

ScheduleBox::ScheduleBox(QWidget *parent) : QWidget(parent)
{
	setMinimumWidth(220);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
    tabs = new ScheduleTab();    
    layout->addWidget(tabs);
    searchBox = new ScheduleSearch();
    layout->addWidget(searchBox);
    list = new ScheduleList(this);
    layout->addWidget(list);
}

ScheduleBox::~ScheduleBox()
{

}

