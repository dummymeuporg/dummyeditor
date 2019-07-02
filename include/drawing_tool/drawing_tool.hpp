#pragma once

class QGraphicsSceneMouseEvent;

namespace DrawingTool {

class DrawingTool {
public:
    DrawingTool();
    virtual void mousePressEvent(::QGraphicsSceneMouseEvent*) = 0;
};

} // namespace DrawingTool
