#include <QGraphicsSceneMouseEvent>

#include "graphicmap/mapgraphicsscene.hpp"
#include "drawing_tool/selection.hpp"

namespace DrawingTool {

Selection::Selection(GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : DrawingTool(mapGraphicsScene, QIcon(":/icons/icon_selection.png")),
      m_mouseClicked(false),
      m_selectionRectItem(nullptr)
{}

void Selection::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void Selection::mapMousePressEvent(::QGraphicsSceneMouseEvent* event) {
    QPoint pt(event->scenePos().toPoint());
    m_startSelection.setX(pt.x() - (pt.x() % 16));
    m_startSelection.setY(pt.y() - (pt.y() % 16));
    m_endSelection = m_startSelection;

    m_mouseClicked = true;

    drawSelection();
}

void Selection::drawSelection() {
    // Remove current selection, if any.
    if (nullptr != m_selectionRectItem) {
        m_mapGraphicsScene.removeItem(m_selectionRectItem);
    }

    QRect rectSelection(
        m_startSelection.x(),
        m_startSelection.y(),
        m_endSelection.x() + 16,
        m_endSelection.y() + 16
    );

    QBrush brush(QColor(66, 135, 245));

    m_selectionRectItem = m_mapGraphicsScene.addRect(rectSelection);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);


}

void Selection::drawGrid() {
    m_mapGraphicsScene.drawGrid(
        m_mapGraphicsScene.width(),
        m_mapGraphicsScene.height(),
        16
    );
}

void Selection::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* event) {
    if (m_mouseClicked) {
        QPoint pt(event->scenePos().toPoint());
        m_endSelection.setX(pt.x() - (pt.x() % 16));
        m_endSelection.setY(pt.y() - (pt.y() % 16));
        drawSelection();
    }
}

void Selection::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) {
    m_mouseClicked = false;

    // XXX: Set in memory selected zone.
}

void Selection::mapKeyPressEvent(::QKeyEvent*) {

}
void Selection::mapKeyReleaseEvent(::QKeyEvent*) {

}

void Selection::mapMouseLeaveEvent() {

}

void Selection::onSelected() {
}

void Selection::onUnselected() {
}

void Selection::emitDrawingToolSelected() {
    DrawingTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

} // namespace DrawingTool
