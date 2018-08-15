#include <QDebug>
#include <QGraphicsRectItem>

#include "dummy/map.h"
#include "misc/mapdocument.h"


#include "graphicmap/graphiclayer.h"
#include "graphicmap/thirdlayerstate.h"
#include "graphicmap/mapgraphicsscene.h"

GraphicMap::ThirdLayerState::ThirdLayerState(
        GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::PaintingGraphicLayerState(mapGraphicsScene)
{

    sceneCleared();

}
GraphicMap::ThirdLayerState::~ThirdLayerState() {
    qDebug() << "Remove third layer states";
    m_mapGraphicsScene.removeItem(m_firstDarkFilter);
    m_mapGraphicsScene.removeItem(m_secondDarkFilter);
}

void GraphicMap::ThirdLayerState::sceneCleared() {
    std::shared_ptr<Dummy::Map> map(m_mapGraphicsScene.mapDocument()->map());
    m_firstDarkFilter = new QGraphicsRectItem(QRect(0,
                                                    0,
                                                    map->width() * 16,
                                                    map->height() * 16));
    m_firstDarkFilter->setBrush(QBrush(QColor(0, 0, 0, 127)));
    m_firstDarkFilter->setZValue(2);

    m_secondDarkFilter = new QGraphicsRectItem(QRect(0,
                                                     0,
                                                     map->width() * 16,
                                                     map->height() * 16));
    m_secondDarkFilter->setBrush(QBrush(QColor(0, 0, 0, 127)));
    m_secondDarkFilter->setZValue(4);

    m_mapGraphicsScene.addItem(m_firstDarkFilter);
    m_mapGraphicsScene.addItem(m_secondDarkFilter);
}

void GraphicMap::ThirdLayerState::adjustLayers() {
    qDebug() << "Third state adjust layers.";
    m_mapGraphicsScene.thirdLayer()->setOpacity(1);
}

void GraphicMap::ThirdLayerState::onNewMap() {
    // Refresh the active layer.
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.thirdLayer());
}
