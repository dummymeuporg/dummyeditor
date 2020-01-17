#include "drawingTool/graphicRectangle.hpp"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "definitions.hpp"
#include "drawingTool/drawingVisitor.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace DrawingTools {

GraphicRectangle::GraphicRectangle(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicPaletteTool(QIcon(":/icons/icon_rect.png"), mapGraphicsScene,
                         visibleGraphicLayer)
{}

void GraphicRectangle::mapMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr == selectionItem()) {
        return;
    }

    m_mouseClicked = true;

    m_firstClickPos = mouseEvent->scenePos().toPoint();
    m_rectangle     = adjustedRectFromP1P2(m_firstClickPos, m_firstClickPos);

    drawHoverPreviewItem();
    m_hoverItem->setPos(m_rectangle.topLeft());
    m_hoverItem->setZValue(Z_PREVIEW);
    mapGraphScene().addItem(m_hoverItem);
}

void GraphicRectangle::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_mouseClicked) {
        QPoint pt(mouseEvent->scenePos().toPoint());

        m_rectangle = adjustedRectFromP1P2(m_firstClickPos, pt);

        drawHoverPreviewItem();
        m_hoverItem->setPos(m_rectangle.topLeft());
        m_hoverItem->setZValue(Z_PREVIEW);
        mapGraphScene().addItem(m_hoverItem);
    }
}

void GraphicRectangle::mapMouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_mouseClicked = false;

    if (nullptr != selectionItem()) {
        applyChipsetSelectionInRectangle();
    }

    m_rectangle = QRect(0, 0, 0, 0);

    if (nullptr != m_hoverItem) {
        mapGraphScene().removeItem(m_hoverItem);
        m_hoverItem = nullptr;
    }
}

void GraphicRectangle::accept(DrawingVisitor& visitor)
{
    visitor.visitTool(*this);
}

void GraphicRectangle::emitDrawingToolSelected()
{
    GraphicPaletteTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void GraphicRectangle::drawHoverPreviewItem()
{
    if (nullptr == selectionItem()) {
        return;
    }

    const QPixmap& chipsetSelection(selectionItem()->pixmap());
    QPixmap dstPixmap(m_rectangle.size());
    QPainter painter(&dstPixmap);

    const int rectW = m_rectangle.width();
    const int rectH = m_rectangle.height();
    const int dX    = chipsetSelection.width();
    const int dY    = chipsetSelection.height();
    for (int y = 0; y < rectH; y += dY) {
        for (int x = 0; x < rectW; x += dX) {
            painter.drawPixmap(QRect(x, y, dX, dY), chipsetSelection);
        }
    }
    if (nullptr != m_hoverItem) {
        mapGraphScene().removeItem(m_hoverItem);
        delete m_hoverItem; // we take ownership from Qt, we need it destroy it
    }
    m_hoverItem = new QGraphicsPixmapItem(dstPixmap);
}

void GraphicRectangle::applyChipsetSelectionInRectangle()
{
    const QPixmap& chipsetSelection(selectionItem()->pixmap());
    const int rectW = m_rectangle.width();
    const int rectH = m_rectangle.height();
    const int dX    = chipsetSelection.width();
    const int dY    = chipsetSelection.height();

    for (int y = 0; y < rectH; y += dY) {
        for (int x = 0; x < rectW; x += dX) {
            applySelectionToMap(static_cast<quint16>(m_rectangle.x() + x),
                                static_cast<quint16>(m_rectangle.y() + y));
        }
    }
}

void GraphicRectangle::applySelectionToMap(quint16 mapX, quint16 mapY)
{
    if (nullptr == visibleGraphicLayer()) {
        return;
    }

    qDebug() << mapX << mapY;

    QPoint point(mapX, mapY);

    const qint16 chipsetX = static_cast<qint16>(rectSelection().x() / CELL_W);
    const qint16 chipsetY = static_cast<qint16>(rectSelection().y() / CELL_H);
    const int selecW      = rectSelection().width();
    const int selecH      = rectSelection().height();

    for (quint16 y = 0; y < selecH; y += CELL_H) {
        for (quint16 x = 0; x < selecW; x += CELL_W) {
            qDebug() << "CHIPSET: " << chipsetX + (x / CELL_W)
                     << chipsetY + (y / CELL_H);
            qDebug() << "TARGET: " << point.x() + (x / CELL_W)
                     << point.y() + (y / CELL_H);
            visibleGraphicLayer()->setTile(static_cast<quint16>(point.x() + x),
                                           static_cast<quint16>(point.y() + y),
                                           chipsetX * CELL_W + x,
                                           chipsetY * CELL_H + y);
        }
    }
}

QRect GraphicRectangle::adjustedRectFromP1P2(const QPoint& p1, const QPoint& p2)
{
    QRect rect(p1, p2);
    rect      = rect.normalized();
    QPoint q1 = rect.topLeft();
    QPoint q2 = rect.bottomRight();
    // round down
    QPoint trueQ1((q1.x() / CELL_W) * CELL_W, (q1.y() / CELL_W) * CELL_W);
    // round up
    QPoint trueQ2(((q2.x() / CELL_H) + 1) * CELL_H,
                  ((q2.y() / CELL_H) + 1) * CELL_H);

    // adjust because rect EXCLUDE its bottom-right point
    return QRect(trueQ1, trueQ2).adjusted(0, 0, -1, -1);
}

} // namespace DrawingTools
