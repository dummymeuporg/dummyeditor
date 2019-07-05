#include <QGraphicsSceneMouseEvent>

#include "graphicmap/visiblegraphiclayer.hpp"

#include "drawing_tool/graphic/pen.hpp"

namespace DrawingTool {

namespace Graphic {

Pen::Pen(QIcon&& icon, GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : Graphic::GraphicTool(std::move(icon), visibleGraphicLayer)
{}

void Pen::mouseMoveEvent(::QGraphicsSceneMouseEvent* event) {

}

void Pen::mousePressEvent(::QGraphicsSceneMouseEvent* event) {

}

void Pen::mouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {

}

} // namespace Graphic

} // namespace DrawingTool
