#include <QDebug>
#include <QRect>

#include "dummy/map.h"
#include "misc/mapdocument.h"

#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/graphiclayer.h"
#include "secondlayerstate.h"

GraphicMap::SecondLayerState::SecondLayerState(
        GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::PaintingLayerState(mapGraphicsScene)
{
    qDebug() << "Second layer state.";
    std::shared_ptr<Dummy::Map> map(m_mapGraphicsScene.mapDocument()->map());

    m_firstDarkFilter = new QGraphicsRectItem(QRect(0,
                                                    0,
                                                    map->width() * 16,
                                                    map->height() * 16));
    m_firstDarkFilter->setBrush(QBrush(QColor(0, 0, 0, 127)));
    m_firstDarkFilter->setZValue(2);

    m_mapGraphicsScene.addItem(m_firstDarkFilter);
}

GraphicMap::SecondLayerState::~SecondLayerState() {
    qDebug() << "Remove second layer state";
     m_mapGraphicsScene.removeItem(m_firstDarkFilter);
}

void GraphicMap::SecondLayerState::paintLayers() {
    // Paint first layer with 100% opacity, etc.
}


void GraphicMap::SecondLayerState::adjustLayers() {
    m_mapGraphicsScene.thirdLayer()->setOpacity(0.5);
}

void GraphicMap::SecondLayerState::onNewMap() {
    // Refresh the active layer.
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.secondLayer());
}
