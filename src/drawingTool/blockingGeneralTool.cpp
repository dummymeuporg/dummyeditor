#include "drawingTool/blockingGeneralTool.hpp"

#include <QDebug>

#include "editor/layerBlocking.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace DrawingTools {

BlockingGeneralTool::BlockingGeneralTool(
        QIcon&& icon,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::BlockingGraphicLayer* blockingGraphicLayer)
    : DrawingTool(mapGraphicsScene, std::move(icon))
    , m_blockingGraphicLayer(blockingGraphicLayer)
{}

void BlockingGeneralTool::emitDrawingToolSelected() {
    // TODO : check if emiting 2 different signals is really what we want?
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void BlockingGeneralTool::drawGrid() {
    if (nullptr == m_blockingGraphicLayer) {
        return;
    }

    m_mapGraphicsScene.drawGrid(
        m_blockingGraphicLayer->layer().width(),
        m_blockingGraphicLayer->layer().height(),
        8
    );
}

void BlockingGeneralTool::setBlockingGraphicLayer(
    GraphicMap::BlockingGraphicLayer* layer)
{
    m_blockingGraphicLayer = layer;
    m_mapGraphicsScene.redrawGrid(); // TODO : this call a commented method... is that the intended purpose?
}

void BlockingGeneralTool::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {
    qDebug() << "Visit blocking layer";
    setBlockingGraphicLayer(&layer);
}

void BlockingGeneralTool::visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) {
    // Do nothing. Not the right tool.
}

} // namespace DrawingTools
