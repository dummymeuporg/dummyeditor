#include "graphicMap/layerGraphicVisible.hpp"

#include <QGraphicsPixmapItem>

#include "editor/layerGraphic.hpp"
#include "editor/map.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "utils/definitions.hpp"

#include "layer_clipboard/visible.hpp"

namespace GraphicMap {

VisibleGraphicLayer::VisibleGraphicLayer(Editor::GraphicLayer& layer, const QPixmap& chipsetPixmap, int zIndex)
    : GraphicMap::MapSceneLayer(zIndex)
    , m_graphicLayer(layer)
    , m_chipsetPixmap(chipsetPixmap)
{
    indexedItems().resize(m_graphicLayer.width() * m_graphicLayer.height());

    connect(&m_graphicLayer, SIGNAL(visibilityChanged(bool)), this, SLOT(setVisibility(bool)));
    connect(&m_graphicLayer, SIGNAL(setSelected()), this, SLOT(setSelected()));

    size_t index = 0;
    for (const auto& cellCoord : m_graphicLayer.layer()) {
        indexedItems()[index] = nullptr;
        qint16 x              = cellCoord.first * CELL_W;
        qint16 y              = cellCoord.second * CELL_H;
        quint16 posX          = (index % m_graphicLayer.width()) * CELL_W;
        quint16 posY          = (index / m_graphicLayer.width()) * CELL_H;

        setTile(posX, posY, x, y);
        ++index;
    }
}

void VisibleGraphicLayer::setSelected()
{
    emit layerSelected(this);
}

void VisibleGraphicLayer::setTile(quint16 x, quint16 y, qint16 chipsetX, qint16 chipsetY)
{
    if (x > (m_graphicLayer.width() * CELL_W) || y > (m_graphicLayer.height() * CELL_H))
        return;

    size_t index = ((y / CELL_H) * m_graphicLayer.width()) + (x / CELL_W);

    if (nullptr != indexedItems()[index]) {
        graphicItems()->removeFromGroup(indexedItems()[index]);
        indexedItems()[index] = nullptr;
    }

    if (chipsetX >= 0 && chipsetY >= 0) {
        indexedItems()[index] =
            new QGraphicsPixmapItem(m_chipsetPixmap.copy(QRect(chipsetX, chipsetY, CELL_W, CELL_H)));
        indexedItems()[index]->setPos(x, y);
        graphicItems()->addToGroup(indexedItems()[index]);

        m_graphicLayer[index] = std::pair<std::int8_t, std::int8_t>(chipsetX / CELL_W, chipsetY / CELL_H);
    } else {
        m_graphicLayer[index] = std::pair<std::int8_t, std::int8_t>(-1, -1);
    }
}

std::shared_ptr<LayerClipboard::Clipboard> VisibleGraphicLayer::getClipboardRegion(const QRect& clip)
{
    const size_t x(clip.x() / CELL_W);
    const size_t y(clip.y() / CELL_H);
    const size_t width(clip.width() / CELL_W);
    const size_t height(clip.height() / CELL_H);

    std::vector<std::pair<std::int8_t, std::int8_t>> content;

    for (unsigned j = y; j <= (y + height); ++j) {
        for (size_t i = x; i <= (x + width); ++i) {
            size_t index((j * m_graphicLayer.width()) + i);
            content.push_back(m_graphicLayer.layer().at(index));
        }
    }

    return std::make_shared<LayerClipboard::Visible>(std::move(clip), std::move(content));
}

} // namespace GraphicMap
