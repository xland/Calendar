#include <QtWidgets/QApplication>
#include "Embed\MainWindow.h"
#include "Util.h"
#include "Embed/Skin.h"
#include "Embed/YearBar.h"
#include "Embed/WeekBar.h"
#include "Embed/DayBtn.h"
#include "Data/Db.h"
#include "Data/Schedules.h"
#include "Eventer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Eventer::init();
    Db::init();
    Schedules::init();
    Skin::init();
    MainWindow::init();
    return a.exec();
}
