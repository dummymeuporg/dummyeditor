#include "graphicmap/mapscenelayer.h"
#include "graphicmap/startingpointlayer.h"

GraphicMap::StartingPointLayer::StartingPointLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::MapSceneLayer(mapGraphicsScene),
      m_startingPointItem(nullptr)
{

}

GraphicMap::StartingPointLayer::~StartingPointLayer()
{

}

GraphicMap::MapSceneLayer&
GraphicMap::StartingPointLayer::setOpacity(qreal opacity)
{
    Q_UNUSED(opacity);
    return *this;
}

GraphicMap::MapSceneLayer&
GraphicMap::StartingPointLayer::removeTile(quint16 x, quint16 y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return *this;
}

