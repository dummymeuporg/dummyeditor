#include "GeneralWindow.hpp"
#include "mainWindow.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    bool useLegacy = true;
    bool useNew    = true;

    MainWindow_Old mainwindowL;
    GeneralWindow mainWindow;

    if (useLegacy) {
        mainwindowL.show();
    }

    if (useNew) {
        mainWindow.show();
    }

    return app.exec();
}
