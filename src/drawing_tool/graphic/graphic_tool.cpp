#include <QDebug>
#include <QGraphicsItem>

#include "editor/graphic_layer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "drawing_tool/graphic/graphic_tool.hpp"
#include "drawing_tool/visitor.hpp"


namespace DrawingTool {
namespace Graphic {

GraphicTool::GraphicTool(
        QIcon&& icon,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : DrawingTool(mapGraphicsScene, std::move(icon)),
      m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicTool::emitDrawingToolSelected() {
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void GraphicTool::drawGrid() {
    if (nullptr != m_visibleGraphicLayer) {
        m_mapGraphicsScene.drawGrid(
            m_visibleGraphicLayer->layer().width(),
            m_visibleGraphicLayer->layer().height(),
            16
        );
    }
}

void
GraphicTool::setVisibleGraphicLayer(GraphicMap::VisibleGraphicLayer* layer)
{
    m_visibleGraphicLayer = layer;
    m_mapGraphicsScene.redrawGrid();
}

void GraphicTool::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    qDebug() << "Visit visible graphic layer";
    setVisibleGraphicLayer(&layer);
}

void GraphicTool::visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) {
    // Nothing to do. Not the right kind of tool.
}

} // namespace Graphic
} // namespace DrawingTool
