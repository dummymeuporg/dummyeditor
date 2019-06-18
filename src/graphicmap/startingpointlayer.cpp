#include <QDebug>
#include <QGraphicsPixmapItem>

#include "core/graphic_map.hpp"
#include "editorproject.hpp"
#include "misc/mapdocument.hpp"
#include "editorstartingpoint.hpp"

#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/mapscenelayer.hpp"
#include "graphicmap/startingpointlayer.hpp"

GraphicMap::StartingPointLayer::StartingPointLayer(
    GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : GraphicMap::MapSceneLayer(mapGraphicsScene),
      m_startingPointItem(nullptr)
{
    std::shared_ptr<Misc::MapDocument> mapDocument(
        m_mapGraphicsScene.mapDocument()
    );
    std::shared_ptr<Dummy::Core::GraphicMap> map(
        m_mapGraphicsScene.mapDocument()->map());
    const EditorProject& project(m_mapGraphicsScene.mapDocument()->project());

    try {
        const EditorStartingPoint& startingPoint = project.startingPoint();

        if (startingPoint.mapName() == mapDocument->mapName())
        {
            qDebug() << "SAME MAP! Set Item.";
            setStartingPointItem(QPoint(startingPoint.x()*16,
                                        startingPoint.y()*16));
        }
    } catch(const ::NoStartingPoint& e) {
        qDebug() << "StartingPointLayer: " << e.what();
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
