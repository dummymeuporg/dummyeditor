#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QScrollArea>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void _initializeProject(const QString&);
    Ui::MainWindow *ui;

private slots:
    void newProject();
//    void openProject();

};

#endif // MAINWINDOW_H




