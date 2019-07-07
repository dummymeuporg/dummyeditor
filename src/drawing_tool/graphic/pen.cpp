#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "graphicmap/visiblegraphiclayer.hpp"

#include "drawing_tool/graphic/pen.hpp"

namespace DrawingTool {

namespace Graphic {

Pen::Pen(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : Graphic::GraphicTool(QIcon(":/icons/icon_pen.png"), visibleGraphicLayer)
{}

void Pen::mouseMoveEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen move.";
}

void Pen::mousePressEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen press.";
}

void Pen::mouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {
    qDebug() << "Pen release.";
}

void Pen::keyPressEvent(::QKeyEvent* event) {
    qDebug() << "key press.";
}

void Pen::keyReleaseEvent(::QKeyEvent* event) {
    qDebug() << "key release.";
}

} // namespace Graphic

} // namespace DrawingTool
