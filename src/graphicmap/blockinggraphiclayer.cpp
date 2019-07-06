#include <QDebug>

#include "drawing_tool/drawing_tool.hpp"

#include "editor/blocking_layer.hpp"
#include "editor/map.hpp"

#include "graphicmap/blockingsquareitem.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

namespace GraphicMap {
BlockingGraphicLayer::BlockingGraphicLayer(
    Editor::BlockingLayer& blockingLayer,
    MapGraphicsScene& mapGraphicsScene,
    int zIndex
) : GraphicMap::GraphicLayer(mapGraphicsScene, zIndex),
    m_blockingLayer(blockingLayer)
{

    m_layerItems.resize(m_blockingLayer.width() * m_blockingLayer.height());

    int index = 0;
    for (auto it = m_blockingLayer.layer().begin();
         it != m_blockingLayer.layer().end();
         ++it, ++index)
    {
        m_layerItems[index] = nullptr;
        if (m_blockingLayer[index])
        {
            qreal posX((index % (m_blockingLayer.width())) * 8);
            qreal posY((index / (m_blockingLayer.width())) * 8);
            _draw(index, quint16(posX), quint16(posY));
        }
    }
}

BlockingGraphicLayer::~BlockingGraphicLayer()
{}

MapSceneLayer&
BlockingGraphicLayer::removeTile(quint16 x, quint16 y)
{
    qDebug() << "Toggle tile." << x << y;
    if (x < m_blockingLayer.width() * 8 && y < m_blockingLayer.height() * 8)
    {

        int index((y/8) * m_blockingLayer.width() + (x/8));
        m_blockingLayer[index] = false;
        if (nullptr != m_layerItems[index])
        {
            m_mapGraphicsScene.removeItem(m_layerItems[index]);
            m_layerItems[index] = nullptr;
        }
   }
    return *this;
}

void BlockingGraphicLayer::toggleTile(quint16 x, quint16 y)
{
    qDebug() << "Toggle tile." << x << y;
    if (x < m_blockingLayer.width() * 8 && y < m_blockingLayer.height() * 8)
    {
        int index((y/8) * m_blockingLayer.width() + (x/8));
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

void BlockingGraphicLayer::setTile(quint16 x, quint16 y, bool isBlocking)
{
    qDebug() << "Set blocking tile." << x << y;
    if (x < m_blockingLayer.width() * 8 && y < m_blockingLayer.height() * 8)
    {
        int index((y/8) * m_blockingLayer.width() + (x/8));

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

void BlockingGraphicLayer::_draw(int index, quint16 x, quint16 y)
{
    m_layerItems[index] = new BlockingSquareItem();
    m_layerItems[index]->setZValue(m_zIndex);
    m_layerItems[index]->setPos(
        QPointF(x - (x % 8), y - (y % 8)));
    m_mapGraphicsScene.addItem(m_layerItems[index]);
}

Editor::Layer& BlockingGraphicLayer::editorLayer() {
    return m_blockingLayer;
}

std::vector<DrawingTool::DrawingTool*>
BlockingGraphicLayer::drawingTools()
{
    // XXX: fill this.
    return {};
}

} // namespace GraphicMap
