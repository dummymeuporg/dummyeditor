#include <QDebug>
#include <QtGlobal>
#include <QPoint>

#include "editorstartingpoint.hpp"
#include "editorproject.hpp"
#include "misc/mapdocument.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/blockinglayerstate.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/selectiondrawingclipboard.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "graphicmap/startingpointlayer.hpp"
#include "graphicmap/startingpointlayerstate.hpp"


GraphicMap::StartingPointLayerState::StartingPointLayerState(
    GraphicMap::MapGraphicsScene& mapGraphicsScene) :
    GraphicMap::PaintingLayerState(mapGraphicsScene,
                                   QPair<int, int>(16, 16))
{

}

GraphicMap::StartingPointLayerState::~StartingPointLayerState()
{

}

void
GraphicMap::StartingPointLayerState::drawWithPen(const QPoint& point)
const
{
    qDebug() << "Draw with pen starting point. " << point;

    // Adjust point
    QPoint adjustedPoint(point.x() - (point.x() % 16),
                         point.y() - (point.y() % 16));

    GraphicMap::StartingPointLayer* layer =
        static_cast<StartingPointLayer*>(m_mapGraphicsScene.activeLayer());
    std::shared_ptr<Dummy::Core::GraphicMap> map(
        m_mapGraphicsScene.mapDocument()->map()
    );
    layer->setStartingPointItem(adjustedPoint);

    // XXX: Fix this
    /*
    m_mapGraphicsScene.project()->setStartingPoint(
        EditorStartingPoint(map->name().toStdString().c_str(),
                             quint16(adjustedPoint.x()/16),
                             quint16(adjustedPoint.y()/16))
    );
    */
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
    m_mapGraphicsScene.startingPointLayer()->setOpacity(1);
}


void GraphicMap::StartingPointLayerState::onNewMap()
{
    m_mapGraphicsScene.setActiveLayer(m_mapGraphicsScene.startingPointLayer());
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
