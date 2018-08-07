#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "dummy/map.h"
#include "dummy/project.h"
#include "misc/mapdocument.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/nodrawingtool.h"


GraphicMap::NoDrawingTool::NoDrawingTool(
    GraphicMap::MapGraphicsScene& mapGraphicScene)
    : GraphicMap::DrawingTool(mapGraphicScene)
{

}

GraphicMap::NoDrawingTool::~NoDrawingTool() {

}

void
GraphicMap::NoDrawingTool::onMousePress(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    Q_UNUSED(mouseEvent);

}

void GraphicMap::NoDrawingTool::chipsetSelectionChanged(
    const QRect& selection)
{
    Q_UNUSED(selection);
}


void
GraphicMap::NoDrawingTool::onMouseMove(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    Q_UNUSED(mouseEvent);
}

void
GraphicMap::NoDrawingTool::onMouseRelease(
    QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
}

void GraphicMap::NoDrawingTool::onMouseLeave()
{

}

