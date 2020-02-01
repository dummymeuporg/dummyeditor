#include "GeneralWindow.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    GeneralWindow mainWindow;

    mainWindow.show();

    return app.exec();
}
