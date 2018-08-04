#include "graphicmap/paintinglayerstate.h"

GraphicMap::PaintingLayerState::PaintingLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : m_mapGraphicsScene(mapGraphicsScene)
{
     onNewMap();
}

GraphicMap::PaintingLayerState::~PaintingLayerState() {

}


void GraphicMap::PaintingLayerState::onNewMap() {

}
