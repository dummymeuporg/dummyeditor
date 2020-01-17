#include "graphicMap/layerGraphicBlocking.hpp"

#include <QDebug>

#include "definitions.hpp"
#include "editor/layerBlocking.hpp"
#include "editor/map.hpp"
#include "graphicMap/graphicItem.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "layer_clipboard/blocking.hpp"

namespace GraphicMap {

BlockingGraphicLayer::BlockingGraphicLayer(Editor::BlockingLayer& blockingLayer,
                                           MapGraphicsScene& mapGraphicsScene,
                                           int zIndex)
    : GraphicMap::GraphicLayer(mapGraphicsScene, zIndex)
    , m_blockingLayer(blockingLayer)
{
    layerItems().resize(m_blockingLayer.layer().size());

    for (size_t index = 0; index < m_blockingLayer.layer().size(); ++index) {
        layerItems()[index] = nullptr;
        if (m_blockingLayer[index] != 0) {
            qreal posX((index % (m_blockingLayer.width())) * BLOCK_W);
            qreal posY((index / (m_blockingLayer.width())) * BLOCK_H);
            draw(static_cast<int>(index), quint16(posX), quint16(posY));
        }
    }
}

BlockingGraphicLayer::~BlockingGraphicLayer() {}
/*
MapSceneLayer& BlockingGraphicLayer::removeTile(quint16 x, quint16 y)
{
    qDebug() << "Toggle tile." << x << y;
    if (x < m_blockingLayer.width() * 8 && y < m_blockingLayer.height() * 8) {
        int index((y / 8) * m_blockingLayer.width() + (x / 8));
        m_blockingLayer[index] = false;
        if (nullptr != m_layerItems[index]) {
            m_mapGraphicsScene.removeItem(m_layerItems[index]);
            m_layerItems[index] = nullptr;
        }
    }
    return *this;
}*/

void BlockingGraphicLayer::toggleTile(quint16 x, quint16 y)
{
    qDebug() << "Toggle tile." << x << y;

    if (x < m_blockingLayer.width() * BLOCK_W
        && y < m_blockingLayer.height() * BLOCK_H) {
        size_t index((y / BLOCK_H) * m_blockingLayer.width() + (x / BLOCK_W));
        qDebug() << "Index: " << index;

        if (m_blockingLayer[index]) {
            m_blockingLayer[index] = false;

            if (nullptr != layerItems()[index]) {
                mapGraphicsScene().removeItem(layerItems()[index]);
                layerItems()[index] = nullptr;
            }
        } else {
            qDebug() << "False!";
            qDebug() << x << y;
            draw(index, x, y);
            m_blockingLayer[index] = true;
        }
    }
}

void BlockingGraphicLayer::setTile(quint16 x, quint16 y, bool isBlocking)
{
    qDebug() << "Set blocking tile." << x << y;
    if (x < m_blockingLayer.width() * BLOCK_W
        && y < m_blockingLayer.height() * BLOCK_H) {
        size_t index((y / BLOCK_H) * m_blockingLayer.width() + (x / BLOCK_W));

        if (nullptr != layerItems()[index]) {
            mapGraphicsScene().removeItem(layerItems()[index]);
            layerItems()[index] = nullptr;
        }

        if (isBlocking) {
            draw(index, x, y);
            m_blockingLayer[index] = true;
        } else {
            m_blockingLayer[index] = false;
        }
    }
}

void BlockingGraphicLayer::erase(int index, quint16 x, quint16 y)
{
    if (nullptr != layerItems()[index]) {
        mapGraphicsScene().removeItem(layerItems()[index]);
        layerItems()[index] = nullptr;
    }
}

void BlockingGraphicLayer::draw(int index, quint16 x, quint16 y)
{
    layerItems()[index] = new GraphicItem(GraphicItem::eBlockingSquareItem);
    layerItems()[index]->setZValue(zIndex());
    layerItems()[index]->setPos(QPointF(x - (x % BLOCK_W), y - (y % BLOCK_H)));
    mapGraphicsScene().addItem(layerItems()[index]);
}

Editor::Layer& BlockingGraphicLayer::editorLayer()
{
    return m_blockingLayer;
}

std::vector<DrawingTools::DrawingTool*> BlockingGraphicLayer::drawingTools()
{
    // XXX: fill this.
    return {/*&m_pen, &m_eraser*/};
}

void BlockingGraphicLayer::accept(GraphicLayerVisitor& visitor)
{
    visitor.visitGraphicLayer(*this);
}

std::shared_ptr<LayerClipboard::Clipboard>
BlockingGraphicLayer::getClipboardRegion(const QRect& clip)
{
    unsigned x(clip.x() / BLOCK_W);
    unsigned y(clip.y() / BLOCK_H);
    unsigned width((clip.width() / BLOCK_W) + 1);
    unsigned height((clip.height() / BLOCK_H) + 1);

    std::vector<std::uint8_t> content;

    for (unsigned j = y; j <= (y + height); ++j) {
        for (unsigned i = x; i <= (x + width); ++i) {
            unsigned index(j * m_blockingLayer.width() + i);
            content.push_back(m_blockingLayer.layer().at(index));
        }
    }

    return std::make_shared<LayerClipboard::Blocking>(std::move(clip),
                                                      std::move(content));
}

} // namespace GraphicMap
