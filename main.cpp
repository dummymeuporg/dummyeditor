#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainwindow;
    mainwindow.show();
//lu
    return app.exec();
}
