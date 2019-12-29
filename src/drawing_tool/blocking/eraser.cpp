#include "drawing_tool/blocking/eraser.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "graphicmap/blockinggraphiclayer.hpp"

namespace DrawingTools {
namespace Blocking {

BlockingEraser::BlockingEraser(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::BlockingGraphicLayer* blockingGraphicLayer)
    : Blocking::BlockingTool(QIcon(":/icons/icon_eraser.png"),
                             mapGraphicsScene,
                             blockingGraphicLayer)
    , m_mouseClicked(false)
{}

void BlockingEraser::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr == m_blockingGraphicLayer) {
        return;
    }

    QPoint point(mouseEvent->scenePos().toPoint());
    point.setX(point.x() - (point.x() % 8));
    point.setY(point.y() - (point.y() % 8));

    if (m_mouseClicked) {
        m_blockingGraphicLayer->setTile(point.x(), point.y(), false);
    }
}

void BlockingEraser::mapMousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Blocking eraser press.";
    if (nullptr == m_blockingGraphicLayer) {
        return;
    }

    QPoint point(event->scenePos().toPoint());
    point.setX(point.x() - (point.x() % 8));
    point.setY(point.y() - (point.y() % 8));
    // XXX: set blocking tile.
    m_blockingGraphicLayer->setTile(point.x(), point.y(), false);

    m_mouseClicked = true;
}

void BlockingEraser::mapMouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Blocking eraser release.";
    m_mouseClicked = false;
}

void BlockingEraser::mapKeyPressEvent(QKeyEvent* event) {
    qDebug() << "key press.";
}

void BlockingEraser::mapKeyReleaseEvent(QKeyEvent* event) {
    qDebug() << "key release.";
}

void BlockingEraser::mapMouseLeaveEvent() {
}

void BlockingEraser::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void BlockingEraser::emitDrawingToolSelected() {
    // TODO : check if emiting 2 different signals is really what we want?
    BlockingTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void BlockingEraser::onUnselected() {
}

void BlockingEraser::onSelected() {
}

} // namespace Blocking
} // namespace DrawingTools
