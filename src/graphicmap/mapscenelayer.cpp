#include "graphicmap/mapscenelayer.hpp"

GraphicMap::MapSceneLayer::MapSceneLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    int zIndex
) : m_mapGraphicsScene(mapGraphicsScene), m_zIndex(zIndex)
{

}

GraphicMap::MapSceneLayer::~MapSceneLayer()
{

}
