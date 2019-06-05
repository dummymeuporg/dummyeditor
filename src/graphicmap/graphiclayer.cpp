#include <QGraphicsItem>

#include "dummy/map.hpp"

#include "graphicmap/graphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"


GraphicMap::GraphicLayer::GraphicLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::MapSceneLayer(mapGraphicsScene),
      m_layerItems(m_mapGraphicsScene.map()->width() *
                   m_mapGraphicsScene.map()->height())
{

}

GraphicMap::GraphicLayer::~GraphicLayer()
{
    for (auto it = m_layerItems.begin(); it != m_layerItems.end(); ++it)
    {
        if(*it != nullptr) {
            m_mapGraphicsScene.removeItem(*it);
        }
    }
}

GraphicMap::MapSceneLayer&
GraphicMap::GraphicLayer::setOpacity(qreal opacity) {
    for (auto it = m_layerItems.begin(); it != m_layerItems.end(); ++it)
    {
        if(*it != nullptr) {
            (*it)->setOpacity(opacity);
        }
    }
    return *this;
}
