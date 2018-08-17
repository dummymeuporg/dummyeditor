#include <QDebug>
#include <QtGlobal>
#include <QPoint>

#include "misc/mapdocument.h"
#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/blockinglayerstate.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/selectiondrawingclipboard.h"
#include "graphicmap/startingpointlayer.h"
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
        layer->toggleTile(quint16(point.x()), quint16(point.y()));
    }
}

void
GraphicMap::BlockingLayerState::drawWithRectangle(
    const QPoint& point, const QRect& rectChipsetSelection) const
{
    GraphicMap::BlockingGraphicLayer* layer =
        static_cast<BlockingGraphicLayer*>(m_mapGraphicsScene.activeLayer());

    for (quint16 j = 0; j < rectChipsetSelection.height()/16; j++)
    {
        for (quint16 i = 0; i < rectChipsetSelection.width()/16; i++)
        {
            layer->toggleTile(quint16(point.x() + i * 16),
                              quint16(point.y() + j * 16));
        }
    }
}

void
GraphicMap::BlockingLayerState::drawWithSelection(
    const QPoint& point,
    const SelectionDrawingClipboard& clipboard) const
{
    int clipboardIndex = 0;
    for(int j = 0;
        j < clipboard.selectionClipboard().height();
        j += 16)
    {
        for (int i = 0;
             i < clipboard.selectionClipboard().width();
             i += 16)
        {

            bool isBlocking(
                clipboard.blockingLayerClipboard()[clipboardIndex]);
            qDebug() << "TOTO " << isBlocking;
            m_mapGraphicsScene.blockingLayer()->setTile(
                quint16(point.x() + i),
                quint16(point.y() + j),
                isBlocking);
        }
    }
}

void GraphicMap::BlockingLayerState::adjustLayers()
{
    m_mapGraphicsScene.firstLayer()->setOpacity(1);
    m_mapGraphicsScene.secondLayer()->setOpacity(1);
    m_mapGraphicsScene.thirdLayer()->setOpacity(1);
    m_mapGraphicsScene.blockingLayer()->setOpacity(1);
    m_mapGraphicsScene.startingPointLayer()->setOpacity(0);
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
