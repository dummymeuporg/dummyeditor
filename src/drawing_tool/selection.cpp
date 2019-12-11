#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "editor/map.hpp"
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

    if (nullptr != m_selectionRectItem) {
        m_mapGraphicsScene.invalidate(m_selectionRectItem->rect());
        m_mapGraphicsScene.removeItem(m_selectionRectItem);
    }

    drawSelection();
}

void Selection::drawSelection() {
    // Remove current selection, if any.

    QPoint start, end;
    if (m_startSelection.x() <= m_endSelection.x()
            && m_startSelection.y() <= m_endSelection.y())
    {
        start = m_startSelection;
        end = m_endSelection;
    }
    else
    {
        end = m_startSelection;
        start = m_endSelection;
    }

    QRect rectSelection(
        start.x(),
        start.y(),
        (end.x() - start.x()) + 16,
        (end.y() - start.y()) + 16
    );

    QBrush brush(QColor(66, 135, 245));

    m_selectionRectItem = m_mapGraphicsScene.addRect(rectSelection);
    m_selectionRectItem->setZValue(99999);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);


}

void Selection::drawGrid() {
    auto map = m_mapGraphicsScene.map();
    if (nullptr != map) {
        m_mapGraphicsScene.drawGrid(
            map->width(),
            map->height(),
            16
        );
    }
}

void Selection::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* event) {
    if (m_mouseClicked) {
        QPoint pt(event->scenePos().toPoint());
        m_endSelection.setX(pt.x() - (pt.x() % 16));
        m_endSelection.setY(pt.y() - (pt.y() % 16));

        if (nullptr != m_selectionRectItem) {
            m_mapGraphicsScene.invalidate(m_selectionRectItem->rect());
            m_mapGraphicsScene.removeItem(m_selectionRectItem);
        }

        drawSelection();
    }
}

void Selection::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) {
    m_mouseClicked = false;

    // XXX: Set in memory selected zone.

}

void Selection::mapKeyPressEvent(::QKeyEvent* event) {
    // If ctrl+c, copy
    if(event->type() == ::QKeyEvent::KeyPress) {
        if(event->matches(QKeySequence::Copy)) {
            onCopyKeyPressed((event));
        }
    }
}

void Selection::onCopyKeyPressed(::QKeyEvent* event) {
    qDebug() << "Copy";
    for (const auto& layer: m_mapGraphicsScene.graphicLayers()) {
        QRect clip(m_startSelection, m_endSelection);
        //layer->getClipboardRegion(clip);
    }
}

void Selection::onCutKeyPressed(::QKeyEvent* event) {
    qDebug() << "Cut";
}

void Selection::onPasteKeyPressed(::QKeyEvent* event) {
    qDebug() << "Paste";
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

void Selection::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    m_mapGraphicsScene.redrawGrid();
}

void Selection::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {
    m_mapGraphicsScene.redrawGrid();
}

} // namespace DrawingTool
