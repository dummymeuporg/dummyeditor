#include <QDebug>
#include <QGraphicsLineItem>
#include <QPen>

#include "core/graphic_map.hpp"

#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/paintinglayerstate.hpp"

GraphicMap::PaintingLayerState::PaintingLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    const QPair<int, int>& gridSize)
    : m_mapGraphicsScene(mapGraphicsScene), m_gridSize(gridSize)
{

}

GraphicMap::PaintingLayerState::~PaintingLayerState() {

}

void GraphicMap::PaintingLayerState::drawGrid()
{
    QPen pen(Qt::black, 0.5);

    // Map should not be null.
    const std::shared_ptr<Dummy::Core::GraphicMap> map(
        m_mapGraphicsScene.map()
    );

    quint16 width = map->width();
    quint16 height = map->height();

    for (int i = 0; i <= width * (16 / m_gridSize.first); ++i) {
        QGraphicsLineItem* item = m_mapGraphicsScene.addLine(
            i * m_gridSize.first,
            0,
            i * m_gridSize.first,
            16 * height,
            pen
        );
        item->setZValue(99);
    }

    for (int i = 0; i <= height * (16 / m_gridSize.second); ++i) {
        QGraphicsLineItem* item = m_mapGraphicsScene.addLine(
            0,
            i * m_gridSize.second,
            16 * width,
            m_gridSize.second * i,
            pen
        );
        item->setZValue(99);
    }
}
