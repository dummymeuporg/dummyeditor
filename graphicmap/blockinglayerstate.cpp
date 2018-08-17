#include <QDebug>
#include <QtGlobal>

#include "misc/mapdocument.h"
#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/blockinglayerstate.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/visiblegraphiclayer.h"

GraphicMap::BlockingLayerState::BlockingLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene)
{

}

GraphicMap::BlockingLayerState::~BlockingLayerState()
{

}

void
GraphicMap::BlockingLayerState::drawWithPen(const QPoint& point)
const
{
    qDebug() << "BlockingLayerState::drawWithPen" << point;
    GraphicMap::BlockingGraphicLayer* layer =
        static_cast<GraphicMap::BlockingGraphicLayer*>(
                m_mapGraphicsScene.activeLayer());

    std::shared_ptr<Dummy::Map> map(
        m_mapGraphicsScene.mapDocument()->map());

    if (map != nullptr)
    {
        QPoint originPoint(point.x() - (point.x() % 16),
                           point.y() - (point.y() % 16));
        qDebug() << originPoint;
        layer->toggleTile(point.x(), point.y());
    }
}

void
GraphicMap::BlockingLayerState::drawWithRectangle(
    const QPoint& point, const QRect& rectChipsetSelection) const
{
    Q_UNUSED(point);
    Q_UNUSED(rectChipsetSelection);
}

void
GraphicMap::BlockingLayerState::drawWithSelection(
    const QPoint& point,
    const SelectionDrawingClipboard& clipboard) const
{
    Q_UNUSED(point);
    Q_UNUSED(clipboard);
}

void GraphicMap::BlockingLayerState::adjustLayers()
{
    m_mapGraphicsScene.firstLayer()->setOpacity(1);
    m_mapGraphicsScene.secondLayer()->setOpacity(1);
    m_mapGraphicsScene.thirdLayer()->setOpacity(1);
    m_mapGraphicsScene.blockingLayer()->setOpacity(1);
}


void GraphicMap::BlockingLayerState::onNewMap()
{
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.blockingLayer());
}

void GraphicMap::BlockingLayerState::sceneCleared()
{

}

void GraphicMap::BlockingLayerState::drawCurrentSelection(
    const QPoint& point, QGraphicsItem* selectionItem) const
{
    Q_UNUSED(point);
    Q_UNUSED(selectionItem);
}
