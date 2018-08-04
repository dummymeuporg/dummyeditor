#include <QDebug>

#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/notpaintingstate.h"
#include "graphicmap/firstlayerstate.h"

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
    m_mapGraphicsScene.setPaitingLayerState(
        new GraphicMap::FirstLayerState(m_mapGraphicsScene));
}
