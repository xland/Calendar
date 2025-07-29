#include <QtWidgets/QApplication>
#include "Util.h"
#include "Embed/MainWindow.h"
#include "Embed/YearBar.h"
#include "Embed/WeekBar.h"
#include "Embed/DayBtn.h"
#include "Data/Db.h"
#include "Data/Schedules.h"
#include "Eventer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    Eventer::init();
    Db::init();
    Schedules::init();
    MainWindow::init();
    return app.exec();
}
