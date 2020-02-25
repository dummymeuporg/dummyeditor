#include "graphicMap/layerGraphicVisible.hpp"

#include <QGraphicsPixmapItem>

#include "editor/layerGraphic.hpp"
#include "editor/map.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "utils/definitions.hpp"

namespace GraphicMap {

VisibleGraphicLayer::VisibleGraphicLayer(Editor::GraphicLayer& layer, const QPixmap& chipsetPixmap, int zIndex)
    : GraphicMap::MapSceneLayer(zIndex)
    , m_graphicLayer(layer)
    , m_chipsetPixmap(chipsetPixmap)
{
    indexedItems().resize(m_graphicLayer.width() * m_graphicLayer.height());

    connect(&m_graphicLayer, &Editor::GraphicLayer::visibilityChanged, this, &MapSceneLayer::setVisibility);
    connect(&m_graphicLayer, &Editor::GraphicLayer::setSelected, this, &VisibleGraphicLayer::setSelected);

    size_t index = 0;
    uint16_t w   = m_graphicLayer.width();
    uint16_t h   = m_graphicLayer.height();
    for (uint16_t x = 0; x < w; ++x)
        for (uint16_t y = 0; y < h; ++y) {
            setTile(x, y, m_graphicLayer.at({x, y}));
            ++index;
        }
}

void VisibleGraphicLayer::setSelected()
{
    emit layerSelected(this);
}

std::pair<int8_t, int8_t> VisibleGraphicLayer::tile(quint16 x, quint16 y) const
{
    if (x > m_graphicLayer.width() || y > m_graphicLayer.height())
        return {-1, -1};
    return m_graphicLayer.at({x, y});
}

void VisibleGraphicLayer::setTile(quint16 x, quint16 y, std::pair<int8_t, int8_t> values)
{
    if (x > m_graphicLayer.width() || y > m_graphicLayer.height())
        return;

    size_t index = (y * m_graphicLayer.width()) + x;

    if (nullptr != indexedItems()[index]) {
        delete indexedItems()[index];
        indexedItems()[index] = nullptr;
    }

    int chipsetX = values.first;
    int chipsetY = values.second;
    if (chipsetX >= 0 && chipsetY >= 0) {
        indexedItems()[index] =
            new QGraphicsPixmapItem(m_chipsetPixmap.copy(QRect(chipsetX * CELL_W, chipsetY * CELL_H, CELL_W, CELL_H)));
        indexedItems()[index]->setPos(x * CELL_W, y * CELL_H);
        graphicItems()->addToGroup(indexedItems()[index]);

        m_graphicLayer.set({x, y}, values);
    } else {
        m_graphicLayer.set({x, y}, {-1, -1});
    }
}

} // namespace GraphicMap
