#include <QDebug>
#include <QRect>

#include "core/graphic_map.hpp"
#include "misc/mapdocument.hpp"

#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/startingpointlayer.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "graphicmap/secondlayerstate.hpp"

GraphicMap::SecondLayerState::SecondLayerState(
        GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::PaintingGraphicLayerState(mapGraphicsScene)
{
    qDebug() << "Second layer state.";


    sceneCleared();
}

GraphicMap::SecondLayerState::~SecondLayerState() {
    qDebug() << "Remove second layer state";
     m_mapGraphicsScene.removeItem(m_firstDarkFilter);
}

void GraphicMap::SecondLayerState::sceneCleared() {
    std::shared_ptr<Dummy::Core::GraphicMap> map(
        m_mapGraphicsScene.mapDocument()->map()
    );
    m_firstDarkFilter = new QGraphicsRectItem(QRect(0,
                                                    0,
                                                    map->width() * 16,
                                                    map->height() * 16));
    m_firstDarkFilter->setBrush(QBrush(QColor(0, 0, 0, 127)));
    m_firstDarkFilter->setZValue(2);

    m_mapGraphicsScene.addItem(m_firstDarkFilter);
}



void GraphicMap::SecondLayerState::adjustLayers() {
    qDebug() << "Second state adjust layers.";
    m_mapGraphicsScene.firstLayer()->setOpacity(1);
    m_mapGraphicsScene.secondLayer()->setOpacity(1);
    m_mapGraphicsScene.thirdLayer()->setOpacity(0.5);
    m_mapGraphicsScene.fourthLayer()->setOpacity(0.25);
    m_mapGraphicsScene.blockingLayer()->setOpacity(0);
    m_mapGraphicsScene.startingPointLayer()->setOpacity(0);
}

void GraphicMap::SecondLayerState::onNewMap() {
    // Refresh the active layer.
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.secondLayer());
}
