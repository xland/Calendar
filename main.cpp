#include "Calendar.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Calendar window;
    window.show();
    return app.exec();
}
