#include "drawingTool/graphicGeneralTool.hpp"

#include <QDebug>

#include "editor/layerGraphic.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "graphicMap/layerGraphicVisible.hpp"

namespace DrawingTools {

GraphicTool::GraphicTool(
        QIcon&& icon,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : DrawingTool(mapGraphicsScene, std::move(icon))
    , m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicTool::emitDrawingToolSelected() {
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void GraphicTool::drawGrid() {
    if (nullptr == m_visibleGraphicLayer) {
        return;
    }

    m_mapGraphicsScene.drawGrid(
        m_visibleGraphicLayer->layer().width(),
        m_visibleGraphicLayer->layer().height(),
        16
    );
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

} // namespace DrawingTools
