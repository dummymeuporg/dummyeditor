#include <QDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

#include "chipsetgraphicsscene.hpp"
#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"

#include "drawing_tool/graphic/pen.hpp"
#include "drawing_tool/visitor.hpp"

namespace DrawingTool {

namespace Graphic {

Pen::Pen(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : Graphic::PaletteTool(QIcon(":/icons/icon_pen.png"), visibleGraphicLayer),
      m_hoverItem(nullptr)
{}

void Pen::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    QPoint pt(mouseEvent->scenePos().toPoint());
    pt.setX(pt.x() - (pt.x() % 16));
    pt.setY(pt.y() - (pt.y() % 16));
    if (nullptr != m_selectionItem) {

        if (m_hoverItem == nullptr ||
                m_hoverItem->pixmap() != m_selectionPixmap)
        {
            m_hoverItem = m_mapGraphicsScene.addPixmap(
                m_selectionItem->pixmap()
            );
            m_hoverItem->setZValue(99999);
        }
        m_hoverItem->setPos(pt);
    }
}

void Pen::mapMousePressEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen press.";

    // XXX: set tiles.
    const QPoint& point(event->scenePos().toPoint());
    const QRect& selectionRect(m_selectionItem->pixmap().rect());
    int width(selectionRect.width() / 16);
    int height(selectionRect.height() / 16);

    for (int j = 0; j < height; ++j) {
        for(int i = 0; i < width; ++i) {
            m_visibleGraphicLayer.setTile(
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

void Pen::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen release.";
}

void Pen::mapKeyPressEvent(::QKeyEvent* event) {
    qDebug() << "key press.";
}

void Pen::mapKeyReleaseEvent(::QKeyEvent* event) {
    qDebug() << "key release.";
}

void Pen::mapMouseLeaveEvent() {
    m_mapGraphicsScene.removeItem(m_hoverItem);
    m_hoverItem = nullptr;
}

void Pen::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void Pen::emitDrawingToolSelected() {
    PaletteTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void Pen::onSelected() {

}

void Pen::onUnselected() {
    PaletteTool::onUnselected();
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


} // namespace Graphic

} // namespace DrawingTool
