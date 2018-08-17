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
    qDebug() << "Toggle tile.";
    if (x < m_mapGraphicsScene.map()->width() * 16
        && y < m_mapGraphicsScene.map()->height() * 16)
    {
        const std::shared_ptr<Dummy::Map> map(m_mapGraphicsScene.map());
        int index((y/16) * map->width() + (x/16));

        if (m_blockingLayer[index])
        {
            m_blockingLayer[index] = false;
            if (nullptr != m_crossItems[index])
            {
                m_mapGraphicsScene.removeItem(m_crossItems[index]);
                m_crossItems[index] = nullptr;
            }

        }
        else
        {
            m_crossItems[index] = new BlockingCrossItem();
            m_mapGraphicsScene.addItem(m_crossItems[index]);
            m_blockingLayer[index] = true;
        }
    }

}
