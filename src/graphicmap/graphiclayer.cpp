#include <iostream>

#include <QDebug>
#include <QGraphicsItem>

#include "editor/map.hpp"

#include "graphicmap/graphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"


GraphicMap::GraphicLayer::GraphicLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::MapSceneLayer(mapGraphicsScene),
      m_layerItems(m_mapGraphicsScene.map()->width() *
                   m_mapGraphicsScene.map()->height())
{

}

GraphicMap::GraphicLayer::~GraphicLayer() {
    /*
    std::cerr << "~VisibleGraphicLayer()" << std::endl;
    for (auto layerItem: m_layerItems)
    {
        std::cerr << "Revome layer item " << layerItem << std::endl;
        if (layerItem != nullptr) {
            m_mapGraphicsScene.removeItem(layerItem);
            layerItem = nullptr;
        }
    }
    */
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
