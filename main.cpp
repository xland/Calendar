#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include "Util.h"
#include "Skin.h"
#include "YearBar.h"
#include "WeekBar.h"
#include "DayBtn.h"
#include "TipInfo.h"
#include "Menu.h"
#include "Toast.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Skin::init();
    MainWindow::init();
    Menu::init();
    YearBar::init();
    WeekBar::init();
    TipInfo::init();
    Toast::init();
    return a.exec();
}
