#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "Util.h"
#include "Skin.h"
#include "YearBar.h"
#include "WeekBar.h"
#include "DayBtn.h"
#include "Db.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Db::init();
    Skin::init();
    MainWindow::init();
    YearBar::init();
    WeekBar::init();
    MainWindow::get()->updateData(QDate::currentDate());
    return a.exec();
}
