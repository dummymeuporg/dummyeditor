#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "dummy/blockinglayer.h"

GraphicMap::BlockingGraphicLayer::BlockingGraphicLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    Dummy::BlockingLayer& blockingLayer)
    : GraphicMap::GraphicLayer(mapGraphicsScene)
{

}

GraphicMap::BlockingGraphicLayer::~BlockingGraphicLayer()
{

}
void GraphicMap::BlockingGraphicLayer::removeTile(quint16, quint16)
{

}
