#include <QtGlobal>

#include "graphicmap/paintingblockinglayerstate.h"

GraphicMap::PaintingBlockingLayerState::PaintingBlockingLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene)
{

}

GraphicMap::PaintingBlockingLayerState::~PaintingBlockingLayerState()
{

}

void
GraphicMap::PaintingBlockingLayerState::drawWithPen(const QPoint& point)
const
{
    Q_UNUSED(point);
}

void
GraphicMap::PaintingBlockingLayerState::drawWithRectangle(
    const QPoint& point,
    const QRect& rectChipsetSelection) const
{
    Q_UNUSED(point);
    Q_UNUSED(rectChipsetSelection);
}

void GraphicMap::PaintingBlockingLayerState::drawWithSelection(
    const QPoint& point,
    const SelectionDrawingClipboard &clipboard) const
{
    Q_UNUSED(point);
    Q_UNUSED(clipboard);

}
