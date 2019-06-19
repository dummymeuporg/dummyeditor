#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>

#include "editorproject.hpp"

namespace Ui {
class MainWindow;
}

namespace GraphicMap {
    class MapGraphicsScene;
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
    void _initializeScenes();
    void _connectScenes();
    void _enableMapCreation();
    void _closeCurrentProject();
    void _loadProject(const QString&);

    Ui::MainWindow *ui;
    std::shared_ptr<EditorProject> m_currentProject;
    ChipsetGraphicsScene* m_chipsetScene;
    GraphicMap::MapGraphicsScene* m_mapScene;

private slots:
    void newProject();
    void openProject();
    void saveProject();
    void selectCurrentMap(QModelIndex);
    void onCancel();
    void onCut();
    void onCopy();
    void onPaste();
};

#endif // MAINWINDOW_H
