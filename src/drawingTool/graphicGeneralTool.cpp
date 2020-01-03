#include "drawingTool/graphicGeneralTool.hpp"

#include <QDebug>

#include "editor/layerGraphic.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "graphicMap/layerGraphicVisible.hpp"

namespace DrawingTools {

GraphicGeneralTool::GraphicGeneralTool(
        QIcon&& icon,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : DrawingTool(mapGraphicsScene, std::move(icon))
    , m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicGeneralTool::emitDrawingToolSelected() {
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void GraphicGeneralTool::drawGrid() {
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
GraphicGeneralTool::setVisibleGraphicLayer(GraphicMap::VisibleGraphicLayer* layer)
{
    m_visibleGraphicLayer = layer;
    m_mapGraphicsScene.redrawGrid();
}

void GraphicGeneralTool::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    qDebug() << "Visit visible graphic layer";
    setVisibleGraphicLayer(&layer);
}

void GraphicGeneralTool::visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) {
    // Nothing to do. Not the right kind of tool.
}

} // namespace DrawingTools
