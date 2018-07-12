#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>

#include "dummy/project.h"

namespace Ui {
class MainWindow;
}

class QGraphicsScene;
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
    std::shared_ptr<Dummy::Project> m_currentProject;
    QAction* m_newMapAction;
    QGraphicsScene* m_chipsetScene;

private slots:
    void newProject();
    void openProject();
    void _onNewMapAction();
};

#endif // MAINWINDOW_H
