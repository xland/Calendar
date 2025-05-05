#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calendar.h"

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = nullptr);
    ~Calendar();

private:
    Ui::CalendarClass ui;
};
