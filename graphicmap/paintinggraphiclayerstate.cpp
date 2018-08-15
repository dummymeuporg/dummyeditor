#include <QPoint>

#include "graphicmap/paintinggraphiclayerstate.h"

GraphicMap::PaintingGraphicLayerState::PaintingGraphicLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene)
{

}

GraphicMap::PaintingGraphicLayerState::~PaintingGraphicLayerState()
{

}

void GraphicMap::PaintingGraphicLayerState::drawWithPen(const QPoint& point)
{
    Q_UNUSED(point);
}

void
GraphicMap::PaintingGraphicLayerState::drawWithRectangle(const QPoint& point)
{
    Q_UNUSED(point);
}

void
GraphicMap::PaintingGraphicLayerState::drawWithSelection(const QPoint& point)
{
    Q_UNUSED(point);
}
