#include <QSplitter>
#include <QLabel>
#include <QHBoxLayout>

#include "DialogSchedule.h"
#include "ScheduleBox.h"
#include "ScheduleEdit.h"

DialogSchedule::DialogSchedule(const QDate& day, QWidget *parent) : QWidget(parent),curDay{day}
{
    setWindowIcon(QIcon(":/Res/logo.ico"));
    setObjectName("DialogSchedule");
    setStyleSheet("#DialogSchedule{background:#ffffff;}");
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
    resize(900, 600);        
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setStyleSheet("QSplitter::handle{ background-color:rgb(200,220,240);}");
    splitter->setContentsMargins(0, 0, 0, 0);
    splitter->setChildrenCollapsible(false);
    auto box = new ScheduleBox(splitter);
    auto editor = new ScheduleEdit(splitter);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
    setWindowTitle(QString("%1年%2月%3日的日程").arg(day.year()).arg(day.month()).arg(day.day()));
}

DialogSchedule::~DialogSchedule()
{

}

