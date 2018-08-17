#include <QGraphicsItem>

#include "dummy/map.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"


GraphicMap::GraphicLayer::GraphicLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : m_mapGraphicsScene(mapGraphicsScene),
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

GraphicMap::GraphicLayer&
GraphicMap::GraphicLayer::setOpacity(qreal opacity) {
    for (auto it = m_layerItems.begin(); it != m_layerItems.end(); ++it)
    {
        if(*it != nullptr) {
            (*it)->setOpacity(opacity);
        }
    }
    return *this;
}
