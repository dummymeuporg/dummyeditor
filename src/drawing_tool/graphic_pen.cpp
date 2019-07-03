#include <QGraphicsSceneMouseEvent>

#include "graphicmap/visiblegraphiclayer.hpp"

#include "drawing_tool/graphic_pen.hpp"

namespace DrawingTool {

GraphicPen::GraphicPen(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicPen::mouseMoveEvent(::QGraphicsSceneMouseEvent* event) {

}

void GraphicPen::mousePressEvent(::QGraphicsSceneMouseEvent* event) {

}

void GraphicPen::mouseReleaseEvent(::QGraphicsSceneMouseEvent* event) {

}

} // namespace DrawingTool
