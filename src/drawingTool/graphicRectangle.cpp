#include "drawingTool/graphicRectangle.hpp"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "graphicMap/layerGraphicVisible.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace DrawingTools {

GraphicRectangle::GraphicRectangle(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicPaletteTool(QIcon(":/icons/icon_rect.png"), mapGraphicsScene,
                         visibleGraphicLayer)
    , m_mouseClicked(false)
    , m_hoverItem(nullptr)
{}

void GraphicRectangle::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (m_mouseClicked) {
        QPoint pt(mouseEvent->scenePos().toPoint());
        pt.setX(pt.x() + (16 - (pt.x() % 16)));
        pt.setY(pt.y() + (16 - (pt.y() % 16)));
        qDebug() << m_rectangle;
        m_rectangle.setBottomRight(pt);

        m_mapGraphicsScene.removeItem(m_selectionItem);
        drawChipsetSelectionInRectangle();
        m_hoverItem->setPos(QPoint(m_rectangle.topLeft()));
        m_hoverItem->setZValue(88888);
        m_mapGraphicsScene.addItem(m_hoverItem);
    }
}

void GraphicRectangle::mapMousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if (nullptr == m_selectionItem) {
        return;
    }

    m_mouseClicked = true;

    QPoint pt(mouseEvent->scenePos().toPoint());

    // Translate the coordinate to get the top upper corner of the tile.
    pt.setX(pt.x() - (pt.x() % 16));
    pt.setY(pt.y() - (pt.y() % 16));

    m_rectangle.setTopLeft(pt);
    m_rectangle.setSize(QSize(16, 16));
    drawChipsetSelectionInRectangle();
    m_hoverItem->setPos(QPoint(m_rectangle.topLeft()));
    m_hoverItem->setZValue(88888);
    m_mapGraphicsScene.addItem(m_hoverItem);
}

void GraphicRectangle::drawChipsetSelectionInRectangle()
{
    if (nullptr == m_selectionItem) {
        return;
    }

    const QPixmap& chipsetSelection(m_selectionItem->pixmap());
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
        m_mapGraphicsScene.removeItem(m_hoverItem);
    }
    m_hoverItem = new QGraphicsPixmapItem(dstPixmap);
}

void GraphicRectangle::mapMouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_mouseClicked = false;

    if (nullptr != m_selectionItem) {
        applyChipsetSelectionInRectangle();
    }

    m_rectangle = QRect(0, 0, 0, 0);

    if (nullptr != m_hoverItem) {
        m_mapGraphicsScene.removeItem(m_hoverItem);
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

void GraphicRectangle::applyChipsetSelectionInRectangle()
{
    const QPixmap& chipsetSelection(m_selectionItem->pixmap());
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
    if (nullptr == m_visibleGraphicLayer) {
        return;
    }

    qDebug() << mapX << mapY;

    QPoint point(mapX, mapY);

    qint16 chipsetX = qint16(m_rectSelection.x() / 16);
    qint16 chipsetY = qint16(m_rectSelection.y() / 16);

    for (quint16 j = 0; j < m_rectSelection.height() / 16; j++) {
        for (quint16 i = 0; i < m_rectSelection.width() / 16; i++) {
            qDebug() << "CHIPSET: " << chipsetX + i << chipsetY + j;
            qDebug() << "TARGET: " << point.x() + i << point.y() + j;
            m_visibleGraphicLayer->setTile(
                quint16(point.x() + i * 16), quint16(point.y() + j * 16),
                (chipsetX + i) * 16, (chipsetY + j) * 16);
        }
    }
}

} // namespace DrawingTools
