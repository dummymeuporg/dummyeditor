#include <QDebug>

#include "drawing_tool/graphic/rectangle.hpp"

namespace DrawingTool {

namespace Graphic {

Rectangle::Rectangle(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : Graphic::PaletteTool(QIcon(":/icons/icon_rectangle.png"),
                           visibleGraphicLayer)
{}

void Rectangle::mapMouseMoveEvent(::QGraphicsSceneMouseEvent* mouseEvent) {
}

void Rectangle::mapMousePressEvent(::QGraphicsSceneMouseEvent* event) {
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
