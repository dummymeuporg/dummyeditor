#include <QDebug>
#include <QGraphicsRectItem>

#include "core/graphic_map.hpp"
#include "misc/mapdocument.hpp"

#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "graphicmap/startingpointlayer.hpp"
#include "graphicmap/thirdlayerstate.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

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
    std::shared_ptr<Dummy::Core::GraphicMap> map(
        m_mapGraphicsScene.mapDocument()->map()
    );
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
    m_mapGraphicsScene.secondLayer()->setOpacity(1);
    m_mapGraphicsScene.thirdLayer()->setOpacity(1);
    m_mapGraphicsScene.fourthLayer()->setOpacity(0.5);
    m_mapGraphicsScene.blockingLayer()->setOpacity(0);
    m_mapGraphicsScene.startingPointLayer()->setOpacity(0);
}

void GraphicMap::ThirdLayerState::onNewMap() {
    // Refresh the active layer.
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.thirdLayer());
}
