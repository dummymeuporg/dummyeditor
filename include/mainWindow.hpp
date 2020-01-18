#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QModelIndex>

#include "drawingTool/drawingVisitor.hpp"
#include "graphicMap/graphicLayerVisitor.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Project;
} // namespace Editor

namespace Ui {
class MainWindow;
}

namespace GraphicMap {
class MapGraphicsScene;
class MapSceneLayer;
class VisibleGraphicLayer;
class BlockingGraphicLayer;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingTool;

namespace Blocking {
class BlockingTool;
} // namespace Blocking

namespace Graphic {
class GraphicTool;
} // namespace Graphic

} // namespace DrawingTools

class ChipsetGraphicsScene;
class QTreeView;

//////////////////////////////////////////////////////////////////////////////
//  MainWindow class
//////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() override;

public slots:
    // automatic connexions
    void on_treeViewMaps_doubleClicked(const QModelIndex& index);
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    // manual connexions
    void setToolboxOnLayer(GraphicMap::MapSceneLayer*);

private:
    void initializeScenes();
    void connectScenes();
    void enableMapCreation();
    void closeCurrentProject();
    void loadProject(const QString&);
    void removeTools();
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow* m_ui                     = nullptr;
    ChipsetGraphicsScene* m_chipsetScene     = nullptr;
    GraphicMap::MapGraphicsScene* m_mapScene = nullptr;
    std::shared_ptr<Editor::Project> m_currentProject;

    std::vector<DrawingTools::DrawingTool*> m_graphicTools {};
    std::vector<DrawingTools::DrawingTool*> m_blockingTools {};
};

#endif // MAINWINDOW_H
