#pragma once
#include <memory>
#include <QAction>
#include <QModelIndex>
#include <QMainWindow>


#include "graphicmap/graphic_layer_visitor.hpp"
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
    class VisibleGraphicLayer;
    class BlockingGraphicLayer;
} // namespace GraphicMap

namespace DrawingTool {
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


class MainWindow : public QMainWindow, public GraphicMap::GraphicLayerVisitor
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
    // Inherited from GraphicMap::GraphicLayerVisitor
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;

private:
    void initializeDrawingTools();
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

    std::vector<DrawingTool::DrawingTool*> m_graphicTools;
    std::vector<DrawingTool::DrawingTool*> m_blockingTools;




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
