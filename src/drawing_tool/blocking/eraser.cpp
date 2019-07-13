#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "chipsetgraphicsscene.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"

#include "drawing_tool/blocking/eraser.hpp"
#include "drawing_tool/visitor.hpp"

namespace DrawingTool {

namespace Blocking {

Eraser::Eraser(GraphicMap::BlockingGraphicLayer& blockingGraphicLayer)
    : Blocking::BlockingTool(QIcon(":/icons/icon_eraser.png"),
                             blockingGraphicLayer),
      m_mouseClicked(false)
{}

void Eraser::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    QPoint point(mouseEvent->scenePos().toPoint());
    point.setX(point.x() - (point.x() % 8));
    point.setY(point.y() - (point.y() % 8));

    if (m_mouseClicked) {
        m_blockingGraphicLayer.setTile(point.x(), point.y(), false);
    }
}

void Eraser::mapMousePressEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Blocking eraser press.";

    QPoint point(event->scenePos().toPoint());
    point.setX(point.x() - (point.x() % 8));
    point.setY(point.y() - (point.y() % 8));
    // XXX: set blocking tile.
    m_blockingGraphicLayer.setTile(point.x(), point.y(), false);

    m_mouseClicked = true;
}

void Eraser::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Blocking eraser release.";
    m_mouseClicked = false;
}

void Eraser::mapKeyPressEvent(::QKeyEvent* event) {
    qDebug() << "key press.";
}

void Eraser::mapKeyReleaseEvent(::QKeyEvent* event) {
    qDebug() << "key release.";
}

void Eraser::mapMouseLeaveEvent() {

}

void Eraser::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void Eraser::emitDrawingToolSelected() {
    BlockingTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void Eraser::onUnselected() {
}

void Eraser::onSelected() {

}


} // namespace Graphic

} // namespace DrawingTool
