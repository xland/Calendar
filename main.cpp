#include <QtWidgets/QApplication>
#include "Util.h"
#include "Embed/MainWindow.h"
#include "Embed/YearBar.h"
#include "Embed/WeekBar.h"
#include "Embed/DayBtn.h"
#include "Data/Db.h"
#include "Data/Schedules.h"
#include "Data/TickTock.h"
#include "Data/Dates.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    Db::init();
    Schedules::init();
    Dates::init();
    TickTock::init();
    MainWindow::init();
    return app.exec();
}
