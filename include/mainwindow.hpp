#pragma once
#include <memory>
#include <QAction>
#include <QModelIndex>
#include <QMainWindow>

#include "drawing_tool/visitor.hpp"

namespace Editor {
class Project;
} // namespace Editor

namespace Ui {
class MainWindow;
}

namespace GraphicMap {
    class MapGraphicsScene;
    class GraphicLayer;
} // namespace GraphicMap

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
    void removeTools();
    void closeEvent (QCloseEvent *event);

    Ui::MainWindow *ui;
    std::shared_ptr<Editor::Project> m_currentProject;
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
    void publishTools(GraphicMap::GraphicLayer*);

};
