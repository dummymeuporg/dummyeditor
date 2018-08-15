#include <QDebug>

#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/notpaintingstate.h"
#include "graphicmap/firstlayerstate.h"

GraphicMap::NotPaintingState::NotPaintingState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::PaintingLayerState(mapGraphicsScene)
{
    qDebug() << "Not painting.";
}

void GraphicMap::NotPaintingState::adjustLayers() {
    // Do nothing.
}

void GraphicMap::NotPaintingState::onNewMap() {
    // Switch to painting first layer.
    m_mapGraphicsScene.setPaitingLayerState(
        new GraphicMap::FirstLayerState(m_mapGraphicsScene));
}

void GraphicMap::NotPaintingState::sceneCleared() {
    // Do nothing.
}

void GraphicMap::NotPaintingState::drawWithPen(const QPoint& point)
{
    // Do nothing.
    Q_UNUSED(point);
}

void GraphicMap::NotPaintingState::drawWithRectangle(const QPoint& point)
{
    // Do nothing.
    Q_UNUSED(point);
}

void GraphicMap::NotPaintingState::drawWithSelection(const QPoint& point)
{
    // Do nothing.
    Q_UNUSED(point);
}
