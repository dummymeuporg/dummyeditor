#include <QDebug>
#include <QGraphicsRectItem>

#include "dummy/map.hpp"
#include "misc/mapdocument.hpp"

#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/fourthlayerstate.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/startingpointlayer.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"


GraphicMap::FourthLayerState::FourthLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::PaintingGraphicLayerState(mapGraphicsScene)
{
    sceneCleared();
}

GraphicMap::FourthLayerState::~FourthLayerState() {
    qDebug() << "Remove fourth layer states";
    m_mapGraphicsScene.removeItem(m_firstDarkFilter);
    m_mapGraphicsScene.removeItem(m_secondDarkFilter);
    m_mapGraphicsScene.removeItem(m_thirdDarkFilter);
}

void GraphicMap::FourthLayerState::sceneCleared()
{
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

    m_thirdDarkFilter = new QGraphicsRectItem(QRect(0,
                                                    0,
                                                    map->width() * 16,
                                                    map->height() * 16));
    m_secondDarkFilter->setBrush(QBrush(QColor(0, 0, 0, 127)));
    m_secondDarkFilter->setZValue(6);

    m_mapGraphicsScene.addItem(m_firstDarkFilter);
    m_mapGraphicsScene.addItem(m_secondDarkFilter);
    m_mapGraphicsScene.addItem(m_thirdDarkFilter);
}

void GraphicMap::FourthLayerState::adjustLayers() {
    qDebug() << "Fourth state adjust layers.";
    m_mapGraphicsScene.thirdLayer()->setOpacity(1);
    m_mapGraphicsScene.secondLayer()->setOpacity(1);
    m_mapGraphicsScene.thirdLayer()->setOpacity(1);
    m_mapGraphicsScene.fourthLayer()->setOpacity(1);
    m_mapGraphicsScene.blockingLayer()->setOpacity(0);
    m_mapGraphicsScene.startingPointLayer()->setOpacity(0);
}

void GraphicMap::FourthLayerState::onNewMap()
{
    // Refresh the active layer.
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.fourthLayer());
}
