#include "drawing_tool/blocking/blocking_tool.hpp"

#include <QDebug>

#include "editor/blocking_layer.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

namespace DrawingTools {
namespace Blocking {

BlockingTool::BlockingTool(
        QIcon&& icon,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::BlockingGraphicLayer* blockingGraphicLayer)
    : DrawingTool(mapGraphicsScene, std::move(icon))
    , m_blockingGraphicLayer(blockingGraphicLayer)
{}

void BlockingTool::emitDrawingToolSelected() {
    // TODO : check if emiting 2 different signals is really what we want?
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void BlockingTool::drawGrid() {
    if (nullptr == m_blockingGraphicLayer) {
        return;
    }

    m_mapGraphicsScene.drawGrid(
        m_blockingGraphicLayer->layer().width(),
        m_blockingGraphicLayer->layer().height(),
        8
    );
}

void BlockingTool::setBlockingGraphicLayer(
    GraphicMap::BlockingGraphicLayer* layer)
{
    m_blockingGraphicLayer = layer;
    m_mapGraphicsScene.redrawGrid(); // TODO : this call a commented method... is that the intended purpose?
}

void BlockingTool::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {
    qDebug() << "Visit blocking layer";
    setBlockingGraphicLayer(&layer);
}

void BlockingTool::visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) {
    // Do nothing. Not the right tool.
}

} // namespace Blocking
} // namespace DrawingTools
