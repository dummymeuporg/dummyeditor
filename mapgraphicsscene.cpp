#include <QGraphicsItem>

#include "dummy/layer.h"
#include "dummy/project.h"

#include "mapgraphicsscene.h"

MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent), m_map(nullptr)
{

}

void MapGraphicsScene::_drawMap() {

}

void MapGraphicsScene::_drawGrid() {

    QPen pen(Qt::black, 0.5);

    quint16 width = m_map->width();
    quint16 height = m_map->height();

    for (int i = 0; i <= width; ++i) {
        QGraphicsItem* item = addLine(i * 16, 0, i * 16, 16 * height, pen);
        item->setZValue(99);
    }

    for (int i = 0; i <= height; ++i) {
        QGraphicsItem* item = addLine(0, i * 16, 16 * width, 16 * i, pen);
        item->setZValue(99);
    }

}

void MapGraphicsScene::_drawLayer(const Dummy::Layer& layer) {
    // TODO.
    Q_UNUSED(layer);
}

MapGraphicsScene&
MapGraphicsScene::setMap(const std::shared_ptr<Dummy::Map>& map) {
    m_map = map;
    const Dummy::Project& project = m_map->project();

    invalidate(m_mapChipset.rect());

    m_mapChipset = QPixmap(project.fullpath() + "/chipsets/"
                           + m_map->chipset());
    clear();

    _drawLayer(m_map->firstLayer());
    _drawGrid();

    return *this;
}

void MapGraphicsScene::changeMap(const std::shared_ptr<Dummy::Map>& map) {
    setMap(map);
}
