#include "drawingTool/drawingSelection.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "drawingTool/drawingVisitor.hpp"
#include "editor/map.hpp"
#include "graphicMap/layerGraphic.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace DrawingTools {

SelectionTool::SelectionTool(GraphicMap::MapGraphicsScene& mapGraphicsScene)
    : DrawingTool(mapGraphicsScene, QIcon(":/icons/icon_selection.png"))
{}

void SelectionTool::accept(DrawingVisitor& visitor)
{
    visitor.visitTool(*this);
}

void SelectionTool::mapMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPoint pt(event->scenePos().toPoint());
    m_startSelection.setX(pt.x() - (pt.x() % 16));
    m_startSelection.setY(pt.y() - (pt.y() % 16));
    m_endSelection = m_startSelection;

    m_mouseClicked = true;

    if (nullptr != m_selectionRectItem) {
        mapGraphScene().invalidate(m_selectionRectItem->rect());
        mapGraphScene().removeItem(m_selectionRectItem);
    }

    drawSelection();
}

void SelectionTool::drawSelection()
{
    // Remove current selection, if any.

    QPoint start, end;
    if (m_startSelection.x() <= m_endSelection.x()
        && m_startSelection.y() <= m_endSelection.y()) {
        start = m_startSelection;
        end   = m_endSelection;
    } else {
        end   = m_startSelection;
        start = m_endSelection;
    }

    QRect rectSelection(start.x(), start.y(), (end.x() - start.x()) + 16,
                        (end.y() - start.y()) + 16);

    QBrush brush(QColor(66, 135, 245));

    m_selectionRectItem = mapGraphScene().addRect(rectSelection);
    m_selectionRectItem->setZValue(99999);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);
}

void SelectionTool::drawGrid()
{
    auto map = mapGraphScene().map();
    if (nullptr != map) {
        mapGraphScene().drawGrid(map->width(), map->height(), 16);
    }
}

void SelectionTool::mapMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_mouseClicked) {
        QPoint pt(event->scenePos().toPoint());
        m_endSelection.setX(pt.x() - (pt.x() % 16));
        m_endSelection.setY(pt.y() - (pt.y() % 16));

        if (nullptr != m_selectionRectItem) {
            mapGraphScene().invalidate(m_selectionRectItem->rect());
            mapGraphScene().removeItem(m_selectionRectItem);
        }

        drawSelection();
    }
}

void SelectionTool::mapMouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    m_mouseClicked = false;

    // XXX: Set in memory selected zone.
}

void SelectionTool::mapKeyPressEvent(QKeyEvent* event)
{
    // If ctrl+c, copy
    if (event->type() == QKeyEvent::KeyPress) {
        if (event->matches(QKeySequence::Copy)) {
            onCopyKeyPressed(event);
        } else if (event->matches(QKeySequence::Paste)) {
            onPasteKeyPressed(event);
        }
    }
}

void SelectionTool::onCopyKeyPressed(QKeyEvent* event)
{
    qDebug() << "Copy";
    m_layers.clear();
    for (const auto& layer : mapGraphScene().graphicLayers()) {
        QRect clip(m_startSelection, m_endSelection);
        m_layers[layer] = layer->getClipboardRegion(clip);
    }
}

void SelectionTool::onCutKeyPressed(QKeyEvent* event)
{
    qDebug() << "Cut";
}

void SelectionTool::onPasteKeyPressed(QKeyEvent* event)
{
    qDebug() << "Paste\r\n layers count: " << m_layers.size() << "\r\n";
    for (auto& [layer, clip] : m_layers) {
        qDebug() << layer << "\r\n";
        clip->setTarget(m_startSelection);
        layer->accept(*clip);
    }
}

void SelectionTool::mapKeyReleaseEvent(QKeyEvent*) {}

void SelectionTool::mapMouseLeaveEvent() {}

void SelectionTool::onSelected() {}

void SelectionTool::onUnselected() {}

void SelectionTool::emitDrawingToolSelected()
{
    // TODO : check if emiting 2 different signals is really what we want?
    DrawingTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void SelectionTool::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer)
{
    mapGraphScene().redrawGrid();
}

void SelectionTool::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer)
{
    mapGraphScene().redrawGrid();
}

} // namespace DrawingTools
