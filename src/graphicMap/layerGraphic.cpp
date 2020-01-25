#include "graphicMap/layerGraphic.hpp"

#include <QGraphicsItem>

#include "graphicMap/mapGraphicsScene.hpp"

namespace GraphicMap {
MapSceneLayer::MapSceneLayer(int zIndex)
    : m_items(new QGraphicsItemGroup)
{
    m_items->setZValue(zIndex);
}

void MapSceneLayer::clear()
{
    for (auto* item : m_items->childItems())
        m_items->removeFromGroup(item);

    m_indexedItems.clear();
}

void MapSceneLayer::setVisibility(bool visible)
{
    m_items->setVisible(visible);
}

} // namespace GraphicMap
