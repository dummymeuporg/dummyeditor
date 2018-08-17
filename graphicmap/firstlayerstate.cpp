#include <QDebug>

#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/visiblegraphiclayer.h"
#include "graphicmap/firstlayerstate.h"
#include "graphicmap/startingpointlayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/graphiclayer.h"

GraphicMap::FirstLayerState::FirstLayerState(
        GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::PaintingGraphicLayerState(mapGraphicsScene)
{
    qDebug() << "First layer state.";

}

GraphicMap::FirstLayerState::~FirstLayerState() {

}

void GraphicMap::FirstLayerState::adjustLayers() {
    qDebug() << "First layer: adjust.";
    m_mapGraphicsScene.secondLayer()->setOpacity(0.5);
    m_mapGraphicsScene.thirdLayer()->setOpacity(0.25);
    m_mapGraphicsScene.blockingLayer()->setOpacity(0);
    m_mapGraphicsScene.startingPointLayer()->setOpacity(0);
}

void GraphicMap::FirstLayerState::onNewMap() {
    // Refresh the active layer.
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.firstLayer());
}

void GraphicMap::FirstLayerState::sceneCleared() {
    // Do nothing.
}
