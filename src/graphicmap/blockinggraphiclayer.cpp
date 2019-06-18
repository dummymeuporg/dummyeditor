#include <QDebug>

#include "core/map.hpp"
#include "core/graphic_map.hpp"

#include "graphicmap/blockingsquareitem.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

GraphicMap::BlockingGraphicLayer::BlockingGraphicLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    Dummy::Core::BlockingLayer& blockingLayer)
    : GraphicMap::GraphicLayer(mapGraphicsScene),
      m_blockingLayer(blockingLayer)
{
    // XXX: Find a better way to resize?
    m_layerItems.resize(m_layerItems.size() * 4);

    const std::shared_ptr<Dummy::Core::GraphicMap> map(
        m_mapGraphicsScene.map()
    );
    int index = 0;
    for (auto it = m_blockingLayer.begin(); it != m_blockingLayer.end();
         ++it, ++index)
    {
        m_layerItems[index] = nullptr;
        qDebug() << "VALUE:" << m_blockingLayer[index];
        if (m_blockingLayer[index])
        {
            qDebug() << "TRUE!";
            qreal posX((index % (map->width()*2)) * 8);
            qreal posY((index / (map->height()*2)) * 8);
            _draw(index, quint16(posX), quint16(posY));
        }
    }
}

GraphicMap::BlockingGraphicLayer::~BlockingGraphicLayer()
{

}

GraphicMap::MapSceneLayer&
GraphicMap::BlockingGraphicLayer::removeTile(quint16 x, quint16 y)
{
    qDebug() << "Toggle tile." << x << y;
    if (x < m_mapGraphicsScene.map()->width() * 16
        && y < m_mapGraphicsScene.map()->height() * 16)
    {
        const std::shared_ptr<Dummy::Core::GraphicMap> map(
            m_mapGraphicsScene.map()
        );
        int index((y/8) * map->width() * 2 + (x/8));
        m_blockingLayer[index] = false;
        if (nullptr != m_layerItems[index])
        {
            m_mapGraphicsScene.removeItem(m_layerItems[index]);
            m_layerItems[index] = nullptr;
        }
   }
    return *this;
}

void GraphicMap::BlockingGraphicLayer::toggleTile(quint16 x, quint16 y)
{
    qDebug() << "Toggle tile." << x << y;
    if (x < m_mapGraphicsScene.map()->width() * 16
        && y < m_mapGraphicsScene.map()->height() * 16)
    {
        const std::shared_ptr<Dummy::Core::GraphicMap> map(
            m_mapGraphicsScene.map()
        );
        int index((y/8) * map->width() * 2 + (x/8));
        qDebug() << "Index: " << index;
        if (m_blockingLayer[index])
        {
            m_blockingLayer[index] = false;
            if (nullptr != m_layerItems[index])
            {
                m_mapGraphicsScene.removeItem(m_layerItems[index]);
                m_layerItems[index] = nullptr;
            }

        }
        else
        {
            qDebug() << "False!";
            qDebug() << x << y;
            _draw(index, x, y);
            m_blockingLayer[index] = true;
        }
    }

}

void GraphicMap::BlockingGraphicLayer::setTile(quint16 x,
                                               quint16 y,
                                               bool isBlocking)
{
    qDebug() << "Set blocking tile." << x << y;
    if (x < m_mapGraphicsScene.map()->width() * 16
        && y < m_mapGraphicsScene.map()->height() * 16)
    {
        const std::shared_ptr<Dummy::Core::GraphicMap> map(
            m_mapGraphicsScene.map()
        );
        int index((y/8) * map->width() * 2 + (x/8));

        if (nullptr != m_layerItems[index])
        {
            m_mapGraphicsScene.removeItem(m_layerItems[index]);
            m_layerItems[index] = nullptr;
        }

        if (isBlocking)
        {
            _draw(index, x, y);
            m_blockingLayer[index] = true;
        }
        else
        {
            m_blockingLayer[index] = false;
        }
    }
}

void
GraphicMap::BlockingGraphicLayer::_draw(int index, quint16 x, quint16 y)
{
    m_layerItems[index] = new BlockingSquareItem();
    m_layerItems[index]->setZValue(50);
    m_layerItems[index]->setPos(
        QPointF(x - (x % 8), y - (y % 8)));
    m_mapGraphicsScene.addItem(m_layerItems[index]);
}
