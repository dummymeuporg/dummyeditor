#include "drawingTool/graphicRectangle.hpp"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

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

    m_firstClickPos = QPoint(mouseEvent->scenePos().toPoint());
    m_rectangle     = adjustedRectFromP1P2(m_firstClickPos, m_firstClickPos);

    drawHoverPreviewItem();
    m_hoverItem->setPos(QPoint(m_rectangle.topLeft()));
    m_hoverItem->setZValue(88888);
    mapGraphScene().addItem(m_hoverItem);
}

void GraphicRectangle::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_mouseClicked) {
        QPoint pt(mouseEvent->scenePos().toPoint());

        m_rectangle = adjustedRectFromP1P2(m_firstClickPos, pt);

        drawHoverPreviewItem();
        m_hoverItem->setPos(QPoint(m_rectangle.topLeft()));
        m_hoverItem->setZValue(88888);
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

void GraphicRectangle::mapKeyPressEvent(QKeyEvent* event)
{
    qDebug() << "key press.";
}

void GraphicRectangle::mapKeyReleaseEvent(QKeyEvent* event)
{
    qDebug() << "key release.";
}

void GraphicRectangle::mapMouseLeaveEvent() {}

void GraphicRectangle::accept(DrawingVisitor& visitor)
{
    visitor.visitTool(*this);
}

void GraphicRectangle::emitDrawingToolSelected()
{
    GraphicPaletteTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void GraphicRectangle::onUnselected()
{
    GraphicPaletteTool::onUnselected();
}

void GraphicRectangle::drawHoverPreviewItem()
{
    if (nullptr == selectionItem()) {
        return;
    }

    const QPixmap& chipsetSelection(selectionItem()->pixmap());
    QPixmap dstPixmap(m_rectangle.size());
    QPainter painter(&dstPixmap);

    for (int j = 0; j < m_rectangle.height(); j += chipsetSelection.height()) {
        for (int i = 0; i < m_rectangle.width();
             i += chipsetSelection.width()) {
            painter.drawPixmap(QRect(i, j, chipsetSelection.width(),
                                     chipsetSelection.height()),
                               chipsetSelection);
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
    for (int j = 0; j < m_rectangle.height(); j += chipsetSelection.height()) {
        for (int i = 0; i < m_rectangle.width();
             i += chipsetSelection.width()) {
            applySelectionToMap(quint16(m_rectangle.x() + i),
                                quint16(m_rectangle.y() + j));
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

    qint16 chipsetX = qint16(rectSelection().x() / 16);
    qint16 chipsetY = qint16(rectSelection().y() / 16);

    for (quint16 j = 0; j < rectSelection().height() / 16; j++) {
        for (quint16 i = 0; i < rectSelection().width() / 16; i++) {
            qDebug() << "CHIPSET: " << chipsetX + i << chipsetY + j;
            qDebug() << "TARGET: " << point.x() + i << point.y() + j;
            visibleGraphicLayer()->setTile(
                quint16(point.x() + i * 16), quint16(point.y() + j * 16),
                (chipsetX + i) * 16, (chipsetY + j) * 16);
        }
    }
}

QRect GraphicRectangle::adjustedRectFromP1P2(const QPoint& p1, const QPoint& p2)
{
    QRect rect(p1, p2);
    rect      = rect.normalized();
    QPoint q1 = rect.topLeft();
    QPoint q2 = rect.bottomRight();
    QPoint trueQ1((q1.x() / 16) * 16, (q1.y() / 16) * 16);         // round down
    QPoint trueQ2((q2.x() / 16 + 1) * 16, (q2.y() / 16 + 1) * 16); // round up

    // adjust because rect EXCLUDE its bottom-right point
    return QRect(trueQ1, trueQ2).adjusted(0, 0, -1, -1);
}

} // namespace DrawingTools
