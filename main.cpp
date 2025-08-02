#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QSharedMemory>
#include "Util.h"
#include "Embed/Flash.h"
#include "Embed/MainWindow.h"
#include "Embed/YearBar.h"
#include "Embed/WeekBar.h"
#include "Embed/DayBtn.h"
#include "Data/Db.h"

bool singleAppCheck() {
    QSharedMemory shared("CalendarUniqueKey");
    if (!shared.create(1)) {
        QMessageBox::warning(nullptr, "通知", "日历应用已在运行中！");
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!singleAppCheck()) {
        return 0;
    }
    app.setQuitOnLastWindowClosed(false);
    AllowSetForegroundWindow(ASFW_ANY);
    Db::init();
    MainWindow::init();
    Flash::init();
    return app.exec();
}
