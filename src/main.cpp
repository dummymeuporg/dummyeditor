#include "GeneralWindow.hpp"
#include "mainWindow.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    bool useLegacy = false;
    if (useLegacy) {
        MainWindow_Old mainwindow;
        mainwindow.show();
        return app.exec();
    } else {
        GeneralWindow mainWindow;
        mainWindow.show();
        return app.exec();
    }
}
