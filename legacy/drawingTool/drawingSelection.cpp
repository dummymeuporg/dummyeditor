#include "legacy/drawingTool/drawingSelection.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <typeinfo>

#include "editor/map.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "graphicMap/mapGraphicsScene.hpp"
#include "legacy/drawingTool/drawingVisitor.hpp"
#include "utils/Logger.hpp"
#include "utils/definitions.hpp"

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
    m_startSelection.setX(pt.x() - (pt.x() % CELL_W));
    m_startSelection.setY(pt.y() - (pt.y() % CELL_H));
    m_endSelection = m_startSelection;

    m_mouseClicked = true;

    drawSelection();
}

void SelectionTool::drawSelection()
{
    // Remove current selection, if any.

    QPoint start;
    QPoint end;

    if (m_startSelection.x() <= m_endSelection.x() && m_startSelection.y() <= m_endSelection.y()) {
        start = m_startSelection;
        end   = m_endSelection;
    } else {
        end   = m_startSelection;
        start = m_endSelection;
    }

    QRect rectSelection(start.x(), start.y(), (end.x() - start.x()) + CELL_W, (end.y() - start.y()) + CELL_H);

    mapGraphScene().setSelection(rectSelection);
}

void SelectionTool::drawGrid() {}

void SelectionTool::mapMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_mouseClicked) {
        QPoint pt(event->scenePos().toPoint());
        m_endSelection.setX(pt.x() - (pt.x() % CELL_W));
        m_endSelection.setY(pt.y() - (pt.y() % CELL_H));

        drawSelection();
    }
}

void SelectionTool::mapMouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    m_mouseClicked = false;

    // XXX: Set in memory selected zone.
}

void SelectionTool::doCopy()
{
    Log::debug(tr("Copy"));
    m_copyClipboard.clear();
    QRect clip(m_startSelection, m_endSelection);

    // copy visible tiles
    for (const auto& pVisLayer : mapGraphScene().graphicLayers()) {
        m_copyClipboard[pVisLayer.get()] = pVisLayer->getClipboardRegion(clip);
    }

    // copy blocking tiles
    for (const auto& pBlockLayer : mapGraphScene().blockingLayers()) {
        m_copyClipboard[pBlockLayer.get()] = pBlockLayer->getClipboardRegion(clip);
    }
}

void SelectionTool::doCut()
{
    Log::debug(tr("TODO : Cut"));
}

void SelectionTool::doPaste()
{
    qDebug() << "Paste\r\n layers count: " << m_copyClipboard.size() << "\r\n";
    for (auto& [layer, clip] : m_copyClipboard) {
        qDebug() << layer << "\r\n";
        clip->setTarget(m_startSelection);
        layer->accept(*clip);
    }
}

void SelectionTool::emitDrawingToolSelected()
{
    // TODO : check if emiting 2 different signals is really what we want?
    DrawingTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void SelectionTool::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {}

void SelectionTool::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {}

void SelectionTool::visitGraphicLayer(GraphicMap::EventsGraphicLayer& layer)
{
    // nothing to do yet
}

} // namespace DrawingTools
