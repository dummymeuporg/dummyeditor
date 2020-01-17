#include "drawingTool/blockingEraser.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "definitions.hpp"
#include "drawingTool/drawingVisitor.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"

namespace DrawingTools {

BlockingEraser::BlockingEraser(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::BlockingGraphicLayer* blockingGraphicLayer)
    : BlockingGeneralTool(QIcon(":/icons/icon_eraser.png"), mapGraphicsScene,
                          blockingGraphicLayer)
{}

void BlockingEraser::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr == blockingLayer()) {
        return;
    }

    QPoint point(mouseEvent->scenePos().toPoint());
    point.setX(point.x() - (point.x() % BLOCK_W));
    point.setY(point.y() - (point.y() % BLOCK_H));

    if (m_mouseClicked) {
        blockingLayer()->setTile(point.x(), point.y(), false);
    }
}

void BlockingEraser::mapMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "Blocking eraser press.";
    if (nullptr == blockingLayer()) {
        return;
    }

    QPoint point(event->scenePos().toPoint());
    point.setX(point.x() - (point.x() % BLOCK_W));
    point.setY(point.y() - (point.y() % BLOCK_H));
    // XXX: set blocking tile.
    blockingLayer()->setTile(point.x(), point.y(), false);

    m_mouseClicked = true;
}

void BlockingEraser::mapMouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "Blocking eraser release.";
    m_mouseClicked = false;
}

void BlockingEraser::accept(DrawingVisitor& visitor)
{
    visitor.visitTool(*this);
}

void BlockingEraser::emitDrawingToolSelected()
{
    // TODO : check if emiting 2 different signals is really what we want?
    BlockingGeneralTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

} // namespace DrawingTools
