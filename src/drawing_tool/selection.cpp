#include "drawing_tool/selection.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "editor/map.hpp"
#include "graphicmap/graphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

namespace DrawingTools {

Selection::Selection(GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : DrawingTool(mapGraphicsScene, QIcon(":/icons/icon_selection.png"))
    , m_mouseClicked(false)
    , m_selectionRectItem(nullptr)
{}

void Selection::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void Selection::mapMousePressEvent(QGraphicsSceneMouseEvent* event) {
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

void Selection::mapMouseMoveEvent(QGraphicsSceneMouseEvent* event) {
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

void Selection::mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) {
    m_mouseClicked = false;

    // XXX: Set in memory selected zone.
}

void Selection::mapKeyPressEvent(QKeyEvent* event) {
    // If ctrl+c, copy
    if (event->type() == QKeyEvent::KeyPress) {
        if (event->matches(QKeySequence::Copy)) {
            onCopyKeyPressed(event);
        } else if (event->matches(QKeySequence::Paste)) {
            onPasteKeyPressed(event);
        }
    }
}

void Selection::onCopyKeyPressed(QKeyEvent* event) {
    qDebug() << "Copy";
    m_layers.clear();
    for (const auto& layer: m_mapGraphicsScene.graphicLayers()) {
        QRect clip(m_startSelection, m_endSelection);
        m_layers[layer] = layer->getClipboardRegion(clip);
    }
}

void Selection::onCutKeyPressed(QKeyEvent* event) {
    qDebug() << "Cut";
}

void Selection::onPasteKeyPressed(QKeyEvent* event) {
    qDebug() << "Paste\r\n layers count: " << m_layers.size() << "\r\n";
    for (auto& [layer, clip] : m_layers) {
        qDebug() << layer << "\r\n";
        clip->setTarget(m_startSelection);
        layer->accept(*clip);
    }
}

void Selection::mapKeyReleaseEvent(QKeyEvent*) {

}

void Selection::mapMouseLeaveEvent() {

}

void Selection::onSelected() {
}

void Selection::onUnselected() {
}

void Selection::emitDrawingToolSelected() {
    // TODO : check if emiting 2 different signals is really what we want?
    DrawingTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void Selection::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    m_mapGraphicsScene.redrawGrid();
}

void Selection::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {
    m_mapGraphicsScene.redrawGrid();
}

} // namespace DrawingTools
