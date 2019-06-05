#include <QGraphicsPixmapItem>

#include "dummy/map.hpp"

#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"

GraphicMap::VisibleGraphicLayer::VisibleGraphicLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    Dummy::Layer& layer,
    const QPixmap& chipsetPixmap,
    int zValue) : GraphicMap::GraphicLayer(mapGraphicsScene),
    m_layer(layer), m_chipsetPixmap(chipsetPixmap), m_zValue(zValue)
{
    const std::shared_ptr<Dummy::Map> map(m_mapGraphicsScene.map());
    int index = 0;
    for (auto it = m_layer.begin();
         it != m_layer.end();
         ++it, ++index)
    {
        m_layerItems[index] = nullptr;
        qint16 x = std::get<0>(*it);
        qint16 y = std::get<1>(*it);
        if (x >= 0 && y >= 0)
        {
            m_layerItems[index] = new QGraphicsPixmapItem(
                m_chipsetPixmap.copy(QRect(x * 16, y * 16, 16, 16)));

            qreal posX = (index % map->width()) * 16;
            qreal posY = (index / map->height()) * 16;

            m_layerItems[index]->setPos(posX, posY);
            m_layerItems[index]->setZValue(m_zValue);
            m_mapGraphicsScene.addItem(m_layerItems[index]);
        }
    }
}

GraphicMap::VisibleGraphicLayer::~VisibleGraphicLayer() {
}


GraphicMap::MapSceneLayer&
GraphicMap::VisibleGraphicLayer::removeTile(quint16 x, quint16 y)
{
    setTile(x, y, -1, -1);
    return *this;
}

GraphicMap::VisibleGraphicLayer&
GraphicMap::VisibleGraphicLayer::setTile(quint16 x,
                                         quint16 y,
                                         qint16 chipsetX,
                                         qint16 chipsetY)
{
    const std::shared_ptr<Dummy::Map> map(m_mapGraphicsScene.map());
    if (x < m_mapGraphicsScene.map()->width() * 16
        && y < m_mapGraphicsScene.map()->height() * 16)
    {
        int index = (y/16) * map->width() + (x/16);

        if (nullptr != m_layerItems[index]) {
            m_mapGraphicsScene.removeItem(m_layerItems[index]);
        }

        if (chipsetX >= 0 && chipsetY >= 0)
        {
            m_layerItems[index] = new
                QGraphicsPixmapItem(
                    m_chipsetPixmap.copy(QRect(chipsetX, chipsetY, 16, 16)));
            m_layerItems[index]->setPos(x, y);
            m_layerItems[index]->setZValue(m_zValue);
            m_mapGraphicsScene.addItem(m_layerItems[index]);
            m_layer.setTile(x / 16, y / 16, chipsetX / 16, chipsetY / 16);

        }
        else
        {
            if (nullptr != m_layerItems[index])
            {
                m_mapGraphicsScene.removeItem(m_layerItems[index]);
                m_layerItems[index] = nullptr;
                m_layer.setTile(x / 16, y / 16, -1, -1);
            }
        }
    }

    return *this;
}
