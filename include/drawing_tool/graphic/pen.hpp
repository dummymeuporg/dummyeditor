#pragma once

#include "drawing_tool/graphic/graphic_tool.hpp"

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class VisibleGraphicLayer;
}

namespace DrawingTool {

namespace Graphic {

class Pen : public GraphicTool {
public:
    Pen(QIcon&&, GraphicMap::VisibleGraphicLayer&);
    void mousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
};

} // namespace Graphic

} // namespace DrawingTool
