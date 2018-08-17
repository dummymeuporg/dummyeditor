#include <QDebug>
#include <QtGlobal>
#include <QPoint>

#include "misc/mapdocument.h"
#include "graphicmap/blockinggraphiclayer.h"
#include "graphicmap/blockinglayerstate.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/paintingblockinglayerstate.h"
#include "graphicmap/selectiondrawingclipboard.h"
#include "graphicmap/visiblegraphiclayer.h"

GraphicMap::PaintingBlockingLayerState::PaintingBlockingLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene)
{

}

GraphicMap::PaintingBlockingLayerState::~PaintingBlockingLayerState()
{

}

void
GraphicMap::PaintingBlockingLayerState::drawWithPen(const QPoint& point)
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
GraphicMap::PaintingBlockingLayerState::drawWithRectangle(
    const QPoint& point,
    const QRect& rectChipsetSelection) const
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

void GraphicMap::PaintingBlockingLayerState::drawWithSelection(
    const QPoint& point,
    const SelectionDrawingClipboard &clipboard) const
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
            m_mapGraphicsScene.blockingLayer()->setTile(
                quint16(point.x() + i * 16),
                quint16(point.y() + j * 16),
                isBlocking);
        }
    }

}
