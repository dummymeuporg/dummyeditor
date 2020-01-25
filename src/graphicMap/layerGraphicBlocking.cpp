#include "graphicMap/layerGraphicBlocking.hpp"

#include <QDebug>

#include "editor/layerBlocking.hpp"
#include "editor/map.hpp"
#include "graphicMap/graphicItem.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "layer_clipboard/blocking.hpp"
#include "utils/Logger.hpp"
#include "utils/definitions.hpp"

namespace GraphicMap {

BlockingGraphicLayer::BlockingGraphicLayer(Editor::BlockingLayer& blockingLayer, int zIndex)
    : GraphicMap::MapSceneLayer(zIndex)
    , m_blockingLayer(blockingLayer)
{
    connect(&m_blockingLayer, SIGNAL(visibilityChanged(bool)), this, SLOT(setVisibility(bool)));
    connect(&m_blockingLayer, SIGNAL(setSelected()), this, SLOT(setSelected()));

    const size_t nbCells = m_blockingLayer.layer().size();
    indexedItems().resize(nbCells);

    for (size_t index = 0; index < nbCells; ++index) {
        if (m_blockingLayer[index] != 0) {
            const size_t posX((index % (m_blockingLayer.width())) * BLOCK_W);
            const size_t posY((index / (m_blockingLayer.width())) * BLOCK_H);

            setTile(static_cast<quint16>(posX), static_cast<quint16>(posY), true);
        }
    }
}

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

void BlockingGraphicLayer::setSelected()
{
    MapSceneLayer::setSelected();
    emit layerSelected(this);
}

void BlockingGraphicLayer::toggleTile(quint16 x, quint16 y)
{
    if (x > (m_blockingLayer.width() * BLOCK_W) || y > (m_blockingLayer.height() * BLOCK_H))
        return;

    size_t index = ((y / BLOCK_H) * m_blockingLayer.width()) + (x / BLOCK_W);

    if (m_blockingLayer[index] != 0) {
        setTile(x, y, false);
    } else {
        setTile(x, y, true);
    }
}

void BlockingGraphicLayer::setTile(quint16 x, quint16 y, bool isBlocking)
{
    if (x > (m_blockingLayer.width() * BLOCK_W) || y < (m_blockingLayer.height() * BLOCK_H))
        return;

    size_t index(((y / BLOCK_H) * m_blockingLayer.width()) + (x / BLOCK_W));

    if (nullptr != indexedItems()[index]) {
        graphicItems()->removeFromGroup(indexedItems()[index]);
        indexedItems()[index] = nullptr;
    }

    if (isBlocking) {
        indexedItems()[index] = new GraphicItem(GraphicItem::eGraphicItemType::eBlockingSquare);
        indexedItems()[index]->setPos(QPointF(x - (x % BLOCK_W), y - (y % BLOCK_H)));
        graphicItems()->addToGroup(indexedItems()[index]);
    }

    m_blockingLayer[index] = isBlocking;
}

std::shared_ptr<LayerClipboard::Clipboard> BlockingGraphicLayer::getClipboardRegion(const QRect& clip)
{
    unsigned x(clip.x() / BLOCK_W);
    unsigned y(clip.y() / BLOCK_H);
    unsigned width((clip.width() / BLOCK_W) + 1);
    unsigned height((clip.height() / BLOCK_H) + 1);

    std::vector<std::uint8_t> content;

    for (unsigned j = y; j <= (y + height); ++j) {
        for (unsigned i = x; i <= (x + width); ++i) {
            unsigned index((j * m_blockingLayer.width()) + i);
            content.push_back(m_blockingLayer.layer().at(index));
        }
    }

    return std::make_shared<LayerClipboard::Blocking>(std::move(clip), std::move(content));
}

} // namespace GraphicMap
