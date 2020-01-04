#include "graphicMap/mapSceneLayer.hpp"

namespace GraphicMap {

MapSceneLayer::MapSceneLayer(MapGraphicsScene& mapGraphicsScene, int zIndex)
    : m_mapGraphicsScene(mapGraphicsScene)
    , m_zIndex(zIndex)
{}

MapSceneLayer::~MapSceneLayer()
{}
} // namespace GraphicMap
