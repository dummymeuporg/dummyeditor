#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "graphicmap/mapgraphicsscene.hpp"
#include "drawing_tool/graphic/rectangle.hpp"

namespace DrawingTool {

namespace Graphic {

Rectangle::Rectangle(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : Graphic::PaletteTool(QIcon(":/icons/icon_rect.png"),
                           visibleGraphicLayer),
      b_mouseClicked(false)
{}

void Rectangle::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
}

void Rectangle::mapMousePressEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
    if (nullptr == m_selectionItem) {
        return;
    }
    b_mouseClicked = true;

    QPoint pt(mouseEvent->scenePos().toPoint());

    // Translate the coordinate to get the top upper corner of the tile.
    pt.setX(pt.x() - (pt.x() % 16));
    pt.setY(pt.y() - (pt.y() % 16));

    m_rectangle.setTopLeft(pt);
    m_rectangle.setSize(QSize(16, 16));

   //drawChipsetSelectionInRectangle();
   //m_selectionItem->setPos(QPoint(m_rectangle.topLeft()));
   //m_selectionItem->setZValue(88888);
   //m_mapGraphicScene.addItem(m_selectionItem);
}

void Rectangle::drawChipsetSelectionInRectangle() {
    if (nullptr != m_selectionItem)
    {
        return;
    }

    const QPixmap& chipsetSelection(m_selectionItem->pixmap());
    QPixmap dstPixmap(m_rectangle.size());
    QPainter painter(&dstPixmap);

    for (int j = 0;
         j < m_rectangle.height();
         j += chipsetSelection.height())
    {
        for (int i = 0;
             i < m_rectangle.width();
             i += chipsetSelection.width())
        {
            painter.drawPixmap(
                QRect(i, j, chipsetSelection.width(),
                      chipsetSelection.height()),
                chipsetSelection);
        }
    }
    if (nullptr != m_selectionItem) {
       m_mapGraphicsScene.removeItem(m_selectionItem);
    }
    m_selectionItem = new QGraphicsPixmapItem(dstPixmap);
}

void Rectangle::mapMouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {
}

void Rectangle::mapKeyPressEvent(::QKeyEvent* event) {
    qDebug() << "key press.";
}

void Rectangle::mapKeyReleaseEvent(::QKeyEvent* event) {
    qDebug() << "key release.";
}

void Rectangle::mapMouseLeaveEvent() {

}

void Rectangle::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void Rectangle::emitDrawingToolSelected() {
    PaletteTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

void Rectangle::onUnselected() {
    PaletteTool::onUnselected();
}

} // namespace Graphic

} // namespace DrawingTool
