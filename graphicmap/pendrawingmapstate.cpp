#include <QGraphicsSceneMouseEvent>

#include "dummy/map.h"
#include "misc/mapdocument.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/pendrawingmapstate.h"

GraphicMap::PenDrawingMapState::PenDrawingMapState(
    GraphicMap::MapGraphicsScene& mapGraphicScene)
    : DrawingMapState(mapGraphicScene)
{

}

GraphicMap::PenDrawingMapState::~PenDrawingMapState() {

}


void
GraphicMap::PenDrawingMapState::onMousePress(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->buttons() & Qt::LeftButton) {
        m_isDrawing = true;
        _setTiles(mouseEvent->scenePos().toPoint());
    }
}

void GraphicMap::PenDrawingMapState::_setTiles(const QPoint& originPoint)
{
    std::shared_ptr<Dummy::Map> map(
        m_mapGraphicScene.mapDocument()->map());

    const QRect& chipsetSelection = m_mapGraphicScene.chipsetSelection();

    int width(chipsetSelection.width() / 16);
    int height(chipsetSelection.height() / 16);

    if (map != nullptr && width >= 0 && height >= 0)
    {
        for (int j = 0; j < height; ++j) {
            for(int i = 0; i < width; ++i) {
                m_mapGraphicScene.activeLayer()->setTile(
                     quint16(originPoint.x()
                             - (originPoint.x() % 16)
                             + (i * 16)),
                     quint16(originPoint.y()
                             - (originPoint.y() % 16)
                             + (j * 16)),
                     qint16(chipsetSelection.x() + (i * 16)),
                     qint16(chipsetSelection.y() + (j * 16)));
            }
        }
    }
}

void
GraphicMap::PenDrawingMapState::onMouseMove(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->buttons() & Qt::LeftButton) {
        if (m_isDrawing) {
            _setTiles(mouseEvent->scenePos().toPoint());
        }
    }
}

void
GraphicMap::PenDrawingMapState::onMouseRelease(
    QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    m_isDrawing = false;
}
