#include "drawingTool/graphicEraser.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "graphicMap/layerGraphicVisible.hpp"

namespace DrawingTools {

GraphicEraser::GraphicEraser(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicTool(QIcon(":/icons/icon_eraser.png"),
                         mapGraphicsScene,
                         visibleGraphicLayer)
    , m_mouseClicked(false)
{}

void GraphicEraser::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr == m_visibleGraphicLayer) {
        return;
    }

    QPoint point(mouseEvent->scenePos().toPoint());
    point.setX(point.x() - (point.x() % 16));
    point.setY(point.y() - (point.y() % 16));
    if (m_mouseClicked) {
        // XXX : remove the tile.
        m_visibleGraphicLayer->setTile(
            quint16(point.x() - (point.x() % 16)),
            quint16(point.y() - (point.y() % 16)),
            -1,
            -1
        );
    }
}

void GraphicEraser::mapMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr == m_visibleGraphicLayer) {
        return;
    }

    QPoint point(mouseEvent->scenePos().toPoint());
    point.setX(point.x() - (point.x() % 16));
    point.setY(point.y() - (point.y() % 16));
    qDebug() << "Eraser press.";

    // XXX: remove tile.
    m_mouseClicked = true;

    m_visibleGraphicLayer->setTile(
        quint16(point.x() - (point.x() % 16)),
        quint16(point.y() - (point.y() % 16)),
        -1,
        -1
    );
}

void GraphicEraser::mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) {
    qDebug() << "Eraser release.";
    m_mouseClicked = false;
}

void GraphicEraser::mapKeyPressEvent(QKeyEvent*) {
    qDebug() << "key press.";
}

void GraphicEraser::mapKeyReleaseEvent(::QKeyEvent*) {
    qDebug() << "key release.";
}

void GraphicEraser::mapMouseLeaveEvent() {
}

void GraphicEraser::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void GraphicEraser::emitDrawingToolSelected() {
    // TODO : check if emiting 2 different signals is really what we want?
    GraphicTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void GraphicEraser::onSelected() {
}

void GraphicEraser::onUnselected() {
}

} // namespace DrawingTools
