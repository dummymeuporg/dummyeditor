#include <QDebug>
#include <QtGlobal>

#include "misc/mapdocument.h"
#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/blockinglayerstate.h"
#include "graphicmap/mapgraphicsscene.h"

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

}


void GraphicMap::BlockingLayerState::onNewMap()
{

}

void GraphicMap::BlockingLayerState::sceneCleared()
{

}
