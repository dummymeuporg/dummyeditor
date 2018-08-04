#include <QDebug>

#include "graphicmap/paintinglayerstate.h"

GraphicMap::PaintingLayerState::PaintingLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : m_mapGraphicsScene(mapGraphicsScene)
{

}

GraphicMap::PaintingLayerState::~PaintingLayerState() {

}
