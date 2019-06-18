#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "core/graphic_map.hpp"
#include "editorproject.hpp"
#include "misc/mapdocument.hpp"

#include "graphicmap/visiblegraphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/nodrawingtool.hpp"


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

void GraphicMap::NoDrawingTool::onKeyPress(QKeyEvent* event)
{
    Q_UNUSED(event);
}

void GraphicMap::NoDrawingTool::onKeyRelease(QKeyEvent* event)
{
    Q_UNUSED(event);
}

