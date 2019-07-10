#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

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
    pt.setX(pt.x() + (16 - (pt.x() % 16)));
    pt.setY(pt.y() + (16 - (pt.y() % 16)));
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

void Pen::accept(Visitor& visitor) {
    visitor.visitTool(*this);
}

void Pen::emitDrawingToolSelected() {
    PaletteTool::emitDrawingToolSelected();
    emit drawingToolSelected(this);
}

} // namespace Graphic

} // namespace DrawingTool
