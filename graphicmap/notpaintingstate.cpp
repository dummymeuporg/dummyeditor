#include <QDebug>

#include "notpaintingstate.h"

GraphicMap::NotPaintingState::NotPaintingState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : PaintingLayerState(mapGraphicsScene)
{
    qDebug() << "Not painting.";
}

void GraphicMap::NotPaintingState::paintLayers() {
    // Do nothing.
}

void GraphicMap::NotPaintingState::adjustLayers() {
    // Do nothing.
}

void GraphicMap::NotPaintingState::onNewMap() {
    // Do nothing.
}
