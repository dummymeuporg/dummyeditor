#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "chipsetgraphicsscene.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"

#include "drawing_tool/blocking/pen.hpp"
#include "drawing_tool/visitor.hpp"

namespace DrawingTool {

namespace Blocking {

Pen::Pen(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::BlockingGraphicLayer* blockingGraphicLayer
) : Blocking::BlockingTool(QIcon(":/icons/icon_pen_2.png"),
                           mapGraphicsScene,
                           blockingGraphicLayer),
      m_mouseClicked(false)
{}

void Pen::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {

    if (nullptr != m_blockingGraphicLayer) {
        QPoint point(mouseEvent->scenePos().toPoint());
        point.setX(point.x() - (point.x() % 8));
        point.setY(point.y() - (point.y() % 8));

        if (m_mouseClicked) {
            // XXX: set blocking tile
            m_blockingGraphicLayer->setTile(point.x(), point.y(), true);
        }
    }
}

void Pen::mapMousePressEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Blocking pen press.";
    if (nullptr != m_blockingGraphicLayer) {
        QPoint point(event->scenePos().toPoint());
        point.setX(point.x() - (point.x() % 8));
        point.setY(point.y() - (point.y() % 8));
        // XXX: set blocking tile.
        m_blockingGraphicLayer->setTile(point.x(), point.y(), true);

        m_mouseClicked = true;
    }
}

void Pen::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen release.";
    m_mouseClicked = false;
}

void Pen::mapKeyPressEvent(::QKeyEvent* event) {
    qDebug() << "key press.";
}

void Pen::mapKeyReleaseEvent(::QKeyEvent* event) {
    qDebug() << "key release.";
}

void Pen::mapMouseLeaveEvent() {

}

void Pen::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void Pen::emitDrawingToolSelected() {
    BlockingTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void Pen::onUnselected() {
}

void Pen::onSelected() {

}


} // namespace Graphic

} // namespace DrawingTool
