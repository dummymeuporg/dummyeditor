#include "legacy/drawingTool/graphicPen.hpp"

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "utils/definitions.hpp"
#include "utils/Logger.hpp"
#include "legacy/drawingTool/drawingVisitor.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace DrawingTools {

GraphicPen::GraphicPen(GraphicMap::MapGraphicsScene& mapGraphicsScene,
                       GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicPaletteTool(QIcon(":/icons/icon_pen.png"), mapGraphicsScene,
                         visibleGraphicLayer)
{}

void GraphicPen::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    QPoint pt(mouseEvent->scenePos().toPoint());
    pt.setX(pt.x() - (pt.x() % CELL_W));
    pt.setY(pt.y() - (pt.y() % CELL_H));

    if (nullptr != selectionItem()) {
        if (m_hoverItem == nullptr
            || m_hoverItem->pixmap().toImage() != selectionPixmap().toImage()) {
            m_hoverItem = mapGraphScene().addPixmap(selectionItem()->pixmap());
            m_hoverItem->setZValue(Z_SELEC);
        }
        m_hoverItem->setPos(pt);
    }

    if (m_mousePressed) {
        drawPattern(mouseEvent);
    }
}

void GraphicPen::mapMousePressEvent(::QGraphicsSceneMouseEvent* event)
{
    Log::debug(tr("Pen press."));

    if (nullptr == selectionItem() || nullptr == visibleGraphicLayer()) {
        return;
    }

    m_mousePressed = true;
    drawPattern(event);
}

void GraphicPen::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent* event)
{
    Log::debug(tr("Pen release."));
    m_mousePressed = false;
}

void GraphicPen::accept(DrawingVisitor& visitor)
{
    visitor.visitTool(*this);
}

void GraphicPen::emitDrawingToolSelected()
{
    GraphicPaletteTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void GraphicPen::onUnselected()
{
    GraphicPaletteTool::onUnselected();
    if (m_hoverItem != nullptr) {
        mapGraphScene().removeItem(m_hoverItem);
        m_hoverItem = nullptr;
    }
    Log::debug(tr("Remove selection item."));
    if (nullptr != selectionItem()) {
        mapGraphScene().removeItem(selectionItem());
        setSelectionItem(nullptr);
    }
}

void GraphicPen::drawPattern(const QGraphicsSceneMouseEvent* event)
{
    const QPoint& point(event->scenePos().toPoint());
    const QRect& selectionRect(selectionItem()->pixmap().rect());
    int width(selectionRect.width() / CELL_W);
    int height(selectionRect.height() / CELL_H);

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            visibleGraphicLayer()->setTile(
                static_cast<quint16>((point.x() - (point.x() % CELL_W))
                                     + (i * CELL_W)),
                static_cast<quint16>((point.y() - (point.y() % CELL_H))
                                     + (j * CELL_H)),
                static_cast<qint16>(rectSelection().x() + (i * CELL_W)),
                static_cast<qint16>(rectSelection().y() + (j * CELL_H)));
        }
    }
}

} // namespace DrawingTools
