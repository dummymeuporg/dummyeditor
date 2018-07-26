#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>

#include "dummy/project.h"

namespace Ui {
class MainWindow;
}

class ChipsetGraphicsScene;
class QTreeView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    void _initializeProject(const QString&);
    void _enableMapCreation();
    void _closeCurrentProject();

    Ui::MainWindow *ui;
    std::shared_ptr<Dummy::Project> m_currentProject;
    ChipsetGraphicsScene* m_chipsetScene;

private slots:
    void newProject();
    void openProject();
    void saveProject();
    void selectCurrentMap(QModelIndex);
};

#endif // MAINWINDOW_H
