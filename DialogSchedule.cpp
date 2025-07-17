#include <QSplitter>
#include <QLabel>
#include <QHBoxLayout>

#include "DialogSchedule.h"
#include "ScheduleBox.h"
#include "ScheduleEdit.h"

DialogSchedule::DialogSchedule(QWidget *parent) : QWidget(parent)
{
    setObjectName("DialogSchedule");
    setStyleSheet("#DialogSchedule{background:#ffffff;}");
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
    resize(800, 600);        
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setStyleSheet("QSplitter::handle { background-color:rgb(200,220,240);}");
    splitter->setContentsMargins(0, 0, 0, 0);
    auto box = new ScheduleBox(splitter);
    auto editor = new ScheduleEdit(splitter);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
}

DialogSchedule::~DialogSchedule()
{

}

