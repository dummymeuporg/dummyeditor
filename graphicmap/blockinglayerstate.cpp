#include <QtGlobal>

#include "graphicmap/blockinglayerstate.h"

GraphicMap::BlockingLayerState::BlockingLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene)
{

}

GraphicMap::BlockingLayerState::~BlockingLayerState()
{

}

void
GraphicMap::BlockingLayerState::drawWithPen(const QPoint& point)
const
{
    Q_UNUSED(point);
}

void
GraphicMap::BlockingLayerState::drawWithRectangle(
    const QPoint& point, const QRect& rectChipsetSelection) const
{
    Q_UNUSED(point);
    Q_UNUSED(rectChipsetSelection);
}

void
GraphicMap::BlockingLayerState::drawWithSelection(
    const QPoint& point,
    const SelectionDrawingClipboard& clipboard) const
{
    Q_UNUSED(point);
    Q_UNUSED(clipboard);
}
