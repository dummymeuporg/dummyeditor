#pragma once

#include "drawing_tool/drawing_tool.hpp"

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class VisibleGraphicLayer;
}

namespace DrawingTool {

class GraphicPen : public DrawingTool {
public:
    GraphicPen(GraphicMap::VisibleGraphicLayer&);
    void mousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
private:
    GraphicMap::VisibleGraphicLayer& m_visibleGraphicLayer;
};

} // namespace DrawingTool
