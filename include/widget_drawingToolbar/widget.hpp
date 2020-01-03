#ifndef DRAWINGTOOLBARWIDGET_H
#define DRAWINGTOOLBARWIDGET_H

#include <QWidget>

#include "drawingTool/drawingVisitor.hpp"
#include "graphicMap/graphicLayerVisitor.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QToolBar;
class QActionGroup;
class ChipsetGraphicsScene;

namespace GraphicMap {
class GraphicLayer;
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTool

namespace DrawingToolbar {
class State;


//////////////////////////////////////////////////////////////////////////////
//  DrawingToolbarWidget class
//////////////////////////////////////////////////////////////////////////////

class Widget : public QWidget,
               public DrawingTools::DrawingVisitor,
               public GraphicMap::GraphicLayerVisitor {
    Q_OBJECT
public:
    Widget(QWidget* parent = nullptr);
    void clear();
    void reset();
    void setState(std::shared_ptr<State>);
    void onLayerSelected(const GraphicMap::MapGraphicsScene*,
                         const ChipsetGraphicsScene*,
                         GraphicMap::GraphicLayer&,
                         std::vector<DrawingTools::DrawingTool*>*);

    const GraphicMap::MapGraphicsScene* mapScene() { return m_mapScene; }

    void setInitialState();

    // DrawingTool::Visitor methods:
    void visitTool(DrawingTools::GraphicPen&) override;
    void visitTool(DrawingTools::GraphicRectangle&) override;
    void visitTool(DrawingTools::GraphicEraser&) override;
    void visitTool(DrawingTools::BlockingEraser&) override;
    void visitTool(DrawingTools::BlockingPen&) override;
    void visitTool(DrawingTools::SelectionTool&) override;

    // GraphicMap::GraphicLayerVisitor methods:
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;


private:
    QToolBar* m_toolbar;
    QActionGroup* m_actionGroup;
    const ChipsetGraphicsScene* m_chipsetGraphicsScene;
    const GraphicMap::MapGraphicsScene* m_mapScene;
    std::vector<DrawingTools::DrawingTool*>* m_drawingTools;
    std::shared_ptr<State> m_state;
};

} // namespace DrawingToolbar

#endif // DRAWINGTOOLBARWIDGET_H
