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

    connect(&m_graphicLayer, SIGNAL(visibilityChanged(bool)), this, SLOT(setVisibility(bool)));
    connect(&m_graphicLayer, SIGNAL(setSelected()), this, SLOT(setSelected()));

    size_t index = 0;
    for (const auto& cellCoord : m_graphicLayer.layer()) {
        indexedItems()[index] = nullptr;
        quint16 posX          = (index % m_graphicLayer.width());
        quint16 posY          = (index / m_graphicLayer.width());

        setTile(posX, posY, cellCoord);
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
    size_t index = (y * m_graphicLayer.width()) + x;
    return m_graphicLayer[index];
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

        m_graphicLayer[index] = values;
    } else {
        m_graphicLayer[index] = std::pair<int8_t, int8_t>(-1, -1);
    }
}

} // namespace GraphicMap
