#include "drawingTool/graphicEraser.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "utils/definitions.hpp"
#include "drawingTool/drawingVisitor.hpp"
#include "graphicMap/layerGraphicVisible.hpp"

namespace DrawingTools {

GraphicEraser::GraphicEraser(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicGeneralTool(QIcon(":/icons/icon_eraser.png"), mapGraphicsScene,
                         visibleGraphicLayer)
{}

void GraphicEraser::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr == visibleGraphicLayer()) {
        return;
    }

    QPoint point(mouseEvent->scenePos().toPoint());
    point.setX(point.x() - (point.x() % CELL_W));
    point.setY(point.y() - (point.y() % CELL_H));
    if (m_mouseClicked) {
        // XXX : remove the tile.
        visibleGraphicLayer()->setTile(
            static_cast<quint16>(point.x() - (point.x() % CELL_W)),
            static_cast<quint16>(point.y() - (point.y() % CELL_H)), -1, -1);
    }
}

void GraphicEraser::mapMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr == visibleGraphicLayer()) {
        return;
    }

    QPoint point(mouseEvent->scenePos().toPoint());
    point.setX(point.x() - (point.x() % CELL_W));
    point.setY(point.y() - (point.y() % CELL_H));
    qDebug() << "Eraser press.";

    // XXX: remove tile.
    m_mouseClicked = true;

    visibleGraphicLayer()->setTile(
        static_cast<quint16>(point.x() - (point.x() % CELL_W)),
        static_cast<quint16>(point.y() - (point.y() % CELL_H)), -1, -1);
}

void GraphicEraser::mapMouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    qDebug() << "Eraser release.";
    m_mouseClicked = false;
}

void GraphicEraser::accept(DrawingVisitor& visitor)
{
    visitor.visitTool(*this);
}

void GraphicEraser::emitDrawingToolSelected()
{
    // TODO : check if emiting 2 different signals is really what we want?
    GraphicGeneralTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

} // namespace DrawingTools
