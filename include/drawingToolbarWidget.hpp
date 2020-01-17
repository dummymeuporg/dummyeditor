#ifndef DRAWINGTOOLBARWIDGET_H
#define DRAWINGTOOLBARWIDGET_H

#include <QToolBar>

#include "drawingTool/drawingVisitor.hpp"
#include "graphicMap/graphicLayerVisitor.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class ChipsetGraphicsScene;
class QActionGroup;

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
    explicit DrawingToolBarWidget(QWidget* parent = nullptr);

    enum class eToolBarState
    {
        NoDrawing,
        Blocking,
        Graphic
    };

    void clear();
    void reset();
    void setState(eToolBarState state);
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
    QToolBar* m_toolbar       = nullptr;
    QActionGroup* m_actionGrp = nullptr;

    const ChipsetGraphicsScene* m_chipsetGraphicsScene      = nullptr;
    const GraphicMap::MapGraphicsScene* m_mapScene          = nullptr;
    std::vector<DrawingTools::DrawingTool*>* m_drawingTools = nullptr;
    eToolBarState m_state = eToolBarState::NoDrawing;
};

#endif // DRAWINGTOOLBARWIDGET_H
