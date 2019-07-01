#include <iostream>

#include <QDebug>
#include <QGraphicsItem>

#include "editor/map.hpp"

#include "graphicmap/graphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

namespace GraphicMap {
GraphicLayer::GraphicLayer(MapGraphicsScene& mapGraphicsScene, int zIndex)
    : MapSceneLayer(mapGraphicsScene, zIndex),
    m_layerItems(m_mapGraphicsScene.map()->width() *
                 m_mapGraphicsScene.map()->height())
{

}

GraphicLayer::~GraphicLayer() {}


void GraphicLayer::setVisibility(bool visible) {
    for (auto it = m_layerItems.begin(); it != m_layerItems.end(); ++it)
    {
        if(*it != nullptr) {
            (*it)->setOpacity(visible * 1);
        }
    }
}

} // namespace GraphicMap
