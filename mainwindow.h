#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTreeView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    void _initializeProject(const QString&);

    Ui::MainWindow *ui;
    QAction* m_newMapAction;

private slots:
    void newProject();
    void openProject();
    void _onNewMapAction();
};

#endif // MAINWINDOW_H
