#include "drawingTool/graphicPen.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "graphicMap/mapGraphicsScene.hpp"
#include "graphicMap/layerGraphicVisible.hpp"

namespace DrawingTools {

GraphicPen::GraphicPen(
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::VisibleGraphicLayer* visibleGraphicLayer)
    : GraphicPaletteTool(QIcon(":/icons/icon_pen.png"),
                                  mapGraphicsScene,
                                  visibleGraphicLayer)
    , m_hoverItem(nullptr)
    , m_mousePressed(false)
{}

void GraphicPen::mapMouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    QPoint pt(mouseEvent->scenePos().toPoint());
    pt.setX(pt.x() - (pt.x() % 16));
    pt.setY(pt.y() - (pt.y() % 16));

    if (nullptr != m_selectionItem) {
        if (m_hoverItem == nullptr
                || m_hoverItem->pixmap() != m_selectionPixmap) {
            m_hoverItem = m_mapGraphicsScene.addPixmap(
                m_selectionItem->pixmap()
            );
            m_hoverItem->setZValue(99999);
        }
        m_hoverItem->setPos(pt);
    }

    if (m_mousePressed) {
        drawPattern(mouseEvent);
    }
}

void GraphicPen::mapMousePressEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen press.";

    if (nullptr == m_selectionItem || nullptr == m_visibleGraphicLayer) {
        return;
    }

    m_mousePressed = true;
    drawPattern(event);
}

void GraphicPen::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen release.";
    m_mousePressed = false;
}

void GraphicPen::mapKeyPressEvent(::QKeyEvent* event) {
    qDebug() << "key press.";
}

void GraphicPen::mapKeyReleaseEvent(::QKeyEvent* event) {
    qDebug() << "key release.";
}

void GraphicPen::mapMouseLeaveEvent() {
    m_mapGraphicsScene.removeItem(m_hoverItem);
    m_hoverItem = nullptr;
}

void GraphicPen::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void GraphicPen::emitDrawingToolSelected() {
    GraphicPaletteTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void GraphicPen::onSelected() {
}

void GraphicPen::onUnselected() {
    GraphicPaletteTool::onUnselected();
    if (m_hoverItem != nullptr) {
        m_mapGraphicsScene.removeItem(m_hoverItem);
        m_hoverItem = nullptr;
    }
    qDebug() << "Remove selection item.";
    if (nullptr != m_selectionItem) {
        m_mapGraphicsScene.removeItem(m_selectionItem);
        m_selectionItem = nullptr;
    }
}

void GraphicPen::drawPattern(QGraphicsSceneMouseEvent* event) {
    const QPoint& point(event->scenePos().toPoint());
    const QRect& selectionRect(m_selectionItem->pixmap().rect());
    int width(selectionRect.width() / 16);
    int height(selectionRect.height() / 16);

    for (int j = 0; j < height; ++j) {
        for(int i = 0; i < width; ++i) {
            m_visibleGraphicLayer->setTile(
                 quint16(point.x()
                         - (point.x() % 16)
                         + (i * 16)),
                 quint16(point.y()
                         - (point.y() % 16)
                         + (j * 16)),
                 qint16(m_rectSelection.x() + (i * 16)),
                 qint16(m_rectSelection.y() + (j * 16))
            );
        }
    }
}

} // namespace DrawingTools
