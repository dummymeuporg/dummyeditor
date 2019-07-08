#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "graphicmap/visiblegraphiclayer.hpp"

#include "drawing_tool/graphic/pen.hpp"
#include "drawing_tool/visitor.hpp"

namespace DrawingTool {

namespace Graphic {

Pen::Pen(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : Graphic::PaletteTool(QIcon(":/icons/icon_pen.png"), visibleGraphicLayer)
{}

void Pen::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen move.";
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
    emit drawingToolSelected(this);
}

} // namespace Graphic

} // namespace DrawingTool
