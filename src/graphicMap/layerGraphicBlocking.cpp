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
    connect(&m_blockingLayer, SIGNAL(visibilityChanged(bool)), this, SLOT(setVisibility(bool)));
    connect(&m_blockingLayer, SIGNAL(setSelected()), this, SLOT(setSelected()));

    const size_t nbCells = m_blockingLayer.layer().size();
    indexedItems().resize(nbCells);

    for (size_t index = 0; index < nbCells; ++index) {
        if (m_blockingLayer[index] != 0) {
            const size_t posX(index % (m_blockingLayer.width()));
            const size_t posY(index / (m_blockingLayer.width()));

            setTile(static_cast<quint16>(posX), static_cast<quint16>(posY), true);
        }
    }
}

void BlockingGraphicLayer::setSelected()
{
    emit layerSelected(this);
}

void BlockingGraphicLayer::toggleTile(quint16 x, quint16 y)
{
    if (x > m_blockingLayer.width() || y > m_blockingLayer.height())
        return;

    size_t index = (y * m_blockingLayer.width() + x);

    if (m_blockingLayer[index] != 0) {
        setTile(x, y, false);
    } else {
        setTile(x, y, true);
    }
}

bool BlockingGraphicLayer::tile(quint16 x, quint16 y) const
{
    if (x > m_blockingLayer.width() || y > m_blockingLayer.height())
        return false;

    return m_blockingLayer[(y * m_blockingLayer.width()) + x];
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

    m_blockingLayer[index] = isBlocking;
}

} // namespace GraphicMap
