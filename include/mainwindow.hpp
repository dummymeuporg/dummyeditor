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
    class GraphicLayer;
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

} // namespace DrawingTool

class ChipsetGraphicsScene;
class QTreeView;

//////////////////////////////////////////////////////////////////////////////
//  MainWindow class
//////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow, public GraphicMap::GraphicLayerVisitor
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;
    // Inherited from GraphicMap::GraphicLayerVisitor
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;

private:
    void initializeDrawingTools();
    void initializeProject(const QString&);
    void initializeScenes();
    void connectScenes();
    void enableMapCreation();
    void closeCurrentProject();
    void loadProject(const QString&);
    void removeTools();
    void closeEvent (QCloseEvent *event);

private slots:
    void newProject();
    void openProject();
    void saveProject();
    void selectCurrentMap(QModelIndex );
    void onCancel();
    void onCut();
    void onCopy();
    void onPaste();
    void publishTools(GraphicMap::GraphicLayer*);

private:
    Ui::MainWindow *m_ui;
    std::shared_ptr<Editor::Project> m_currentProject;
    ChipsetGraphicsScene* m_chipsetScene;
    GraphicMap::MapGraphicsScene* m_mapScene;

    DrawingTools::Selection* m_selectionDrawingTool;
    std::vector<DrawingTools::DrawingTool*> m_graphicTools;
    std::vector<DrawingTools::DrawingTool*> m_blockingTools;
};

#endif // MAINWINDOW_H
