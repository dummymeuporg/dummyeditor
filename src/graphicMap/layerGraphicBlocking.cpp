#include "graphicMap/layerGraphicBlocking.hpp"

#include <QDebug>

#include "editor/layerBlocking.hpp"
#include "editor/map.hpp"
#include "graphicMap/graphicItem.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "utils/Logger.hpp"
#include "utils/definitions.hpp"

namespace GraphicMap {

BlockingGraphicLayer::BlockingGraphicLayer(Editor::BlockingLayer& blockingLayer, int zIndex)
    : GraphicMap::MapSceneLayer(zIndex)
    , m_blockingLayer(blockingLayer)
{
    connect(&m_blockingLayer, &Editor::GraphicLayer::visibilityChanged, this, &MapSceneLayer::setVisibility);
    connect(&m_blockingLayer, &Editor::GraphicLayer::setSelected, this, &BlockingGraphicLayer::setSelected);

    const size_t nbCells = m_blockingLayer.layer().size();
    indexedItems().resize(nbCells);

    uint16_t w = m_blockingLayer.layer().width();
    uint16_t h = m_blockingLayer.layer().height();

    for (uint16_t x = 0; x < w; ++x)
        for (uint16_t y = 0; y < h; ++y)
            if (m_blockingLayer.at({x, y}) != 0)
                setTile(x, y, 1);
}

void BlockingGraphicLayer::setSelected()
{
    emit layerSelected(this);
}

void BlockingGraphicLayer::toggleTile(quint16 x, quint16 y)
{
    if (x > m_blockingLayer.width() || y > m_blockingLayer.height())
        return;

    if (m_blockingLayer.at({x, y}) != 0) {
        setTile(x, y, false);
    } else {
        setTile(x, y, true);
    }
}

bool BlockingGraphicLayer::tile(quint16 x, quint16 y) const
{
    if (x > m_blockingLayer.width() || y > m_blockingLayer.height())
        return false;

    return m_blockingLayer.at({x, y});
}

void BlockingGraphicLayer::setTile(quint16 x, quint16 y, bool isBlocking)
{
    if (x > m_blockingLayer.width() || y > m_blockingLayer.height())
        return;

    size_t index((y * m_blockingLayer.width()) + x);

    if (nullptr != indexedItems()[index]) {
        delete indexedItems()[index];
        indexedItems()[index] = nullptr;
    }

    if (isBlocking) {
        indexedItems()[index] = new GraphicItem(GraphicItem::eGraphicItemType::eBlockingSquare);
        indexedItems()[index]->setPos(QPointF(x * BLOCK_W, y * BLOCK_H));
        graphicItems()->addToGroup(indexedItems()[index]);
    }

    m_blockingLayer.set({x, y}, isBlocking);
}

} // namespace GraphicMap
