#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "dummy/map.h"
#include "dummy/project.h"
#include "misc/mapdocument.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"
#include "graphicmap/rectangledrawingtool.h"


GraphicMap::RectangleDrawingTool::RectangleDrawingTool(
    GraphicMap::MapGraphicsScene& mapGraphicScene)
    : GraphicMap::DrawingTool(mapGraphicScene), m_selectionItem(nullptr)
{

}

GraphicMap::RectangleDrawingTool::~RectangleDrawingTool() {

}

void
GraphicMap::RectangleDrawingTool::onMousePress(
    QGraphicsSceneMouseEvent* mouseEvent)
{

}

void GraphicMap::RectangleDrawingTool::chipsetSelectionChanged(
    const QRect& selection)
{

}


void
GraphicMap::RectangleDrawingTool::onMouseMove(
    QGraphicsSceneMouseEvent* mouseEvent)
{

}

void
GraphicMap::RectangleDrawingTool::onMouseRelease(
    QGraphicsSceneMouseEvent* event)
{

}

void GraphicMap::RectangleDrawingTool::onMouseLeave()
{

}
