#include "dummy/layer.h"

#include "mapgraphicsscene.h"

MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent), m_map(nullptr)
{

}

void MapGraphicsScene::_drawMap() {

}

void MapGraphicsScene::_drawLayer(const Dummy::Layer& layer) {

}

MapGraphicsScene&
MapGraphicsScene::setMap(const std::shared_ptr<Dummy::Map>& map) {
    m_map = map;
    //m_mapchipset = QPixmap(m_map);
}
