#pragma once

#include <QWidget>

#include "ScheduleList.h"
#include "ScheduleTab.h"
#include "ScheduleSearch.h"

class ScheduleBox : public QWidget
{
	Q_OBJECT

public:
	ScheduleBox(QWidget *parent = nullptr);
	~ScheduleBox();
	ScheduleList* list;
	ScheduleTab* tabs;
	ScheduleSearch* searchBox;
private:
};

