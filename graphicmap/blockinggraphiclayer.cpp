#include <QDebug>

#include "graphicmap/blockingcrossitem.h"
#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "dummy/blockinglayer.h"
#include "dummy/map.h"

GraphicMap::BlockingGraphicLayer::BlockingGraphicLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    Dummy::BlockingLayer& blockingLayer)
    : GraphicMap::GraphicLayer(mapGraphicsScene),
      m_blockingLayer(blockingLayer)
{
    const std::shared_ptr<Dummy::Map> map(m_mapGraphicsScene.map());
    int index = 0;
    for (auto it = m_blockingLayer.begin(); it != m_blockingLayer.end();
         ++it, ++index)
    {
        m_layerItems[index] = nullptr;
        qDebug() << "VALUE:" << m_blockingLayer[index];
        if (m_blockingLayer[index])
        {
            qDebug() << "TRUE!";
            qreal posX((index % map->width()) * 16);
            qreal posY((index / map->height()) * 16);
            _drawCross(index, quint16(posX), quint16(posY));
        }
    }
}

GraphicMap::BlockingGraphicLayer::~BlockingGraphicLayer()
{

}

void GraphicMap::BlockingGraphicLayer::removeTile(quint16 x, quint16 y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
}

void GraphicMap::BlockingGraphicLayer::toggleTile(quint16 x, quint16 y)
{
    qDebug() << "Toggle tile." << x << y;
    if (x < m_mapGraphicsScene.map()->width() * 16
        && y < m_mapGraphicsScene.map()->height() * 16)
    {
        const std::shared_ptr<Dummy::Map> map(m_mapGraphicsScene.map());
        int index((y/16) * map->width() + (x/16));
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
            _drawCross(index, x, y);
            m_blockingLayer[index] = true;
        }
    }

}

void GraphicMap::BlockingGraphicLayer::_drawCross(int index,
                                                  quint16 x,
                                                  quint16 y)
{
    m_layerItems[index] = new BlockingCrossItem();
    m_layerItems[index]->setZValue(7);
    m_layerItems[index]->setPos(
        QPointF(x - (x % 16), y - (y % 16)));
    m_mapGraphicsScene.addItem(m_layerItems[index]);
}
