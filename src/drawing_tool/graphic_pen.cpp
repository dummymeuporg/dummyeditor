#include <QGraphicsSceneMouseEvent>

#include "graphicmap/visiblegraphiclayer.hpp"

#include "drawing_tool/graphic_pen.hpp"

namespace DrawingTool {

GraphicPen::GraphicPen(GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicPen::mouseMoveEvent(::QGraphicsSceneMouseEvent *) {}
void GraphicPen::mousePressEvent(::QGraphicsSceneMouseEvent *) {}
void GraphicPen::mouseReleaseEvent(::QGraphicsSceneMouseEvent *) {}

} // namespace DrawingTool
