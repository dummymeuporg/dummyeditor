#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QScrollArea>

#include <chipsetcell.h>
#include <mapcell.h>

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

    int m_coordXactif;
    int m_coordYactif;

    bool m_testSouris;

    QPixmap *chipsetBase;
    QList<QList<mapCell *>> labelbis;
    QList<QList<QGraphicsProxyWidget *>> labelter;

private slots:
    void newProject();
//    void openProject();

public slots:
    void receptionCoord(int coordX, int coordY);
    void receptionEtatSouris(bool etatSouris);
    void coloriage(int coordX, int coordY);
};

#endif // MAINWINDOW_H




