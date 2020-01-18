#include "drawingTool/graphicGeneralTool.hpp"

#include <QDebug>

#include "definitions.hpp"
#include "editor/layerGraphic.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace DrawingTools {

GraphicGeneralTool::GraphicGeneralTool(
    QIcon&& icon, GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : DrawingTool(mapGraphicsScene, std::move(icon))
    , m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicGeneralTool::emitDrawingToolSelected()
{
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

GraphicMap::VisibleGraphicLayer* GraphicGeneralTool::visibleGraphicLayer()
{
    return m_visibleGraphicLayer;
}

void GraphicGeneralTool::drawGrid()
{
    if (nullptr == m_visibleGraphicLayer) {
        return;
    }

    mapGraphScene().drawGrid(m_visibleGraphicLayer->layer().width(),
                             m_visibleGraphicLayer->layer().height(), CELL_W);
}

void GraphicGeneralTool::setVisibleGraphicLayer(
    GraphicMap::VisibleGraphicLayer* layer)
{
    m_visibleGraphicLayer = layer;
    mapGraphScene().redrawGrid();
}

void GraphicGeneralTool::visitGraphicLayer(
    GraphicMap::VisibleGraphicLayer& layer)
{
    qDebug() << "Visit visible graphic layer";
    setVisibleGraphicLayer(&layer);
}
void GraphicGeneralTool::visitGraphicLayer(
    GraphicMap::EventsGraphicLayer& layer)
{
    qDebug() << "Visit event graphic layer";
}

void GraphicGeneralTool::visitGraphicLayer(GraphicMap::BlockingGraphicLayer&)
{
    // Nothing to do. Not the right kind of tool.
}

} // namespace DrawingTools
