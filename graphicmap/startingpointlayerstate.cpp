#include <QDebug>
#include <QtGlobal>
#include <QPoint>

#include "misc/mapdocument.h"
#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/blockinglayerstate.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/selectiondrawingclipboard.h"
#include "graphicmap/visiblegraphiclayer.h"
#include "graphicmap/startingpointlayerstate.h"


GraphicMap::StartingPointLayerState::StartingPointLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene)
{

}

GraphicMap::StartingPointLayerState::~StartingPointLayerState()
{

}

void
GraphicMap::StartingPointLayerState::drawWithPen(const QPoint& point)
const
{
    Q_UNUSED(point);
    qDebug() << "Draw with pen starting point. " << point;
}

void
GraphicMap::StartingPointLayerState::drawWithRectangle(
    const QPoint& point, const QRect& rectChipsetSelection) const
{
    Q_UNUSED(point);
    Q_UNUSED(rectChipsetSelection);
}

void
GraphicMap::StartingPointLayerState::drawWithSelection(
    const QPoint& point,
    const SelectionDrawingClipboard& clipboard) const
{
    Q_UNUSED(point);
    Q_UNUSED(clipboard);
}

void GraphicMap::StartingPointLayerState::adjustLayers()
{
    m_mapGraphicsScene.firstLayer()->setOpacity(1);
    m_mapGraphicsScene.secondLayer()->setOpacity(1);
    m_mapGraphicsScene.thirdLayer()->setOpacity(1);
    m_mapGraphicsScene.blockingLayer()->setOpacity(0);
}


void GraphicMap::StartingPointLayerState::onNewMap()
{
    //m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.blockingLayer());
}

void GraphicMap::StartingPointLayerState::sceneCleared()
{

}

void GraphicMap::StartingPointLayerState::drawCurrentSelection(
    const QPoint& point, QGraphicsItem* selectionItem) const
{
    Q_UNUSED(point);
    Q_UNUSED(selectionItem);
}
