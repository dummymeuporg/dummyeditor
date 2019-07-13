#include <QDebug>
#include <QGraphicsItem>

#include "editor/blocking_layer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"
#include "drawing_tool/blocking/blocking_tool.hpp"
#include "drawing_tool/visitor.hpp"


namespace DrawingTool {
namespace Blocking {

BlockingTool::BlockingTool(
        QIcon&& icon,
        GraphicMap::BlockingGraphicLayer& blockingGraphicLayer)
    : DrawingTool(blockingGraphicLayer.mapGraphicsScene(), std::move(icon)),
      m_blockingGraphicLayer(blockingGraphicLayer)
{}

void BlockingTool::emitDrawingToolSelected() {
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void BlockingTool::drawGrid() {
    m_mapGraphicsScene.drawGrid(
        m_blockingGraphicLayer.layer().width(),
        m_blockingGraphicLayer.layer().height(),
        8
    );
}

} // namespace Graphic
} // namespace DrawingTool
