#ifndef DRAWINGTOOLBARWIDGET_H
#define DRAWINGTOOLBARWIDGET_H

#include <QToolBar>

#include "drawingTool/drawingVisitor.hpp"
#include "graphicMap/graphicLayerVisitor.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class ChipsetGraphicsScene;

namespace GraphicMap {
class GraphicLayer;
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTools

//////////////////////////////////////////////////////////////////////////////
//  DrawingToolbarWidget class
//////////////////////////////////////////////////////////////////////////////

class DrawingToolBarWidget : public QWidget,
                             public DrawingTools::DrawingVisitor,
                             public GraphicMap::GraphicLayerVisitor
{
    Q_OBJECT
public:
    DrawingToolBarWidget(QWidget* parent = nullptr);

    enum tToolBarState
    {
        NoDrawingToolState,
        BlockingToolsState,
        GraphicToolsState
    };

    void clear();
    void reset();
    void setState(tToolBarState state);
    void onLayerSelected(const GraphicMap::MapGraphicsScene*,
                         const ChipsetGraphicsScene*, GraphicMap::GraphicLayer&,
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
    QActionGroup* m_actionGrp;

    const ChipsetGraphicsScene* m_chipsetGraphicsScene;
    const GraphicMap::MapGraphicsScene* m_mapScene;
    std::vector<DrawingTools::DrawingTool*>* m_drawingTools;
    tToolBarState m_state;
};

#endif // DRAWINGTOOLBARWIDGET_H
