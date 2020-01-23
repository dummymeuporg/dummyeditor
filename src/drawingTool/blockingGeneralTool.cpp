#include "drawingTool/blockingGeneralTool.hpp"

#include "utils/definitions.hpp"
#include "utils/Logger.hpp"
#include "editor/layerBlocking.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace DrawingTools {

BlockingGeneralTool::BlockingGeneralTool(
    QIcon&& icon, GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::BlockingGraphicLayer* blockingGraphicLayer)
    : DrawingTool(mapGraphicsScene, std::move(icon))
    , m_blockingGraphicLayer(blockingGraphicLayer)
{}

void BlockingGeneralTool::emitDrawingToolSelected()
{
    // TODO : check if emiting 2 different signals is really what we want?
    DrawingTool::emitDrawingToolSelected();
    Log::info(tr("Emit drawing tool selected."));
    emit drawingToolSelected(this);
}

GraphicMap::BlockingGraphicLayer* BlockingGeneralTool::blockingLayer()
{
    return m_blockingGraphicLayer;
}

void BlockingGeneralTool::drawGrid()
{
    if (nullptr == m_blockingGraphicLayer) {
        return;
    }

    mapGraphScene().drawGrid(m_blockingGraphicLayer->layer().width(),
                             m_blockingGraphicLayer->layer().height(), BLOCK_W);
}

void BlockingGeneralTool::setBlockingGraphicLayer(
    GraphicMap::BlockingGraphicLayer* layer)
{
    m_blockingGraphicLayer = layer;
    mapGraphScene().redrawGrid(); // TODO : this call a commented method...
                                  // is that the intended purpose?
}

void BlockingGeneralTool::visitGraphicLayer(
    GraphicMap::BlockingGraphicLayer& layer)
{
    Log::info(tr("Visit blocking layer"));
    setBlockingGraphicLayer(&layer);
}

void BlockingGeneralTool::visitGraphicLayer(
    GraphicMap::EventsGraphicLayer& layer)
{
    Log::info(tr("Visit event layer"));
}

void BlockingGeneralTool::visitGraphicLayer(GraphicMap::VisibleGraphicLayer&)
{
    // Do nothing. Not the right tool.
}

} // namespace DrawingTools
