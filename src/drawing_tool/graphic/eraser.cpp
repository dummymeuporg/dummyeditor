#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "chipsetgraphicsscene.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"

#include "drawing_tool/graphic/eraser.hpp"
#include "drawing_tool/visitor.hpp"

namespace DrawingTool {

namespace Graphic {

Eraser::Eraser(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : Graphic::GraphicTool(QIcon(":/icons/icon_eraser.png"),
                           visibleGraphicLayer)
{}

void Eraser::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    QPoint pt(mouseEvent->scenePos().toPoint());
    pt.setX(pt.x() - (pt.x() % 16));
    pt.setY(pt.y() - (pt.y() % 16));
    if (m_mouseClicked) {
        // XXX : remove the tile.
    }
}

void Eraser::mapMousePressEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Eraser press.";

    // XXX: remove tile.
    m_mouseClicked = true;
}

void Eraser::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Eraser release.";
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
    GraphicTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void Eraser::onSelected() {

}

void Eraser::onUnselected() {

}


} // namespace Graphic

} // namespace DrawingTool
