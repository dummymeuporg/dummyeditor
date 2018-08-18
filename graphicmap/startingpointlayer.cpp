#include <QDebug>
#include <QGraphicsPixmapItem>

#include "dummy/map.h"
#include "dummy/project.h"
#include "misc/mapdocument.h"
#include "dummy/startingpoint.h"

#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/mapscenelayer.h"
#include "graphicmap/startingpointlayer.h"

GraphicMap::StartingPointLayer::StartingPointLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::MapSceneLayer(mapGraphicsScene),
      m_startingPointItem(nullptr)
{
    std::shared_ptr<Dummy::Map> map(
        m_mapGraphicsScene.mapDocument()->map());
    const Dummy::Project& project(map->project());
    const Dummy::StartingPoint* startingPoint = project.startingPoint();

    if (nullptr != startingPoint && startingPoint->mapName() == map->name())
    {
        qDebug() << "SAME MAP! Set Item.";
        setStartingPointItem(QPoint(startingPoint->x()*16,
                                    startingPoint->y()*16));
    }

}

GraphicMap::StartingPointLayer::~StartingPointLayer()
{

}

GraphicMap::MapSceneLayer&
GraphicMap::StartingPointLayer::setOpacity(qreal opacity)
{
    if (nullptr != m_startingPointItem)
    {
        m_startingPointItem->setOpacity(opacity);
    }
    return *this;
}

GraphicMap::MapSceneLayer&
GraphicMap::StartingPointLayer::removeTile(quint16 x, quint16 y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return *this;
}

void GraphicMap::StartingPointLayer::setStartingPointItem(const QPoint& point)
{
    qDebug() << "Starting point at " << point;
    if (nullptr != m_startingPointItem)
    {
        m_mapGraphicsScene.removeItem(m_startingPointItem);
        m_startingPointItem = nullptr;
    }

    m_startingPointItem = new QGraphicsPixmapItem(
        QPixmap::fromImage(QImage(":/icons/icon_prog2.png").scaled(16, 16)));
    m_startingPointItem->setPos(point);
    m_startingPointItem->setZValue(50);
    m_mapGraphicsScene.addItem(m_startingPointItem);

}
