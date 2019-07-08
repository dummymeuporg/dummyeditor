#pragma once

#include "drawing_tool/graphic/graphic_tool.hpp"

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class VisibleGraphicLayer;
}

namespace DrawingTool {

namespace Graphic {

class Pen : public GraphicTool {
    Q_OBJECT
public:
    Pen(GraphicMap::VisibleGraphicLayer&);
    void accept(Visitor&) override;
    void mapMousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(::QKeyEvent*) override;
    void mapKeyReleaseEvent(::QKeyEvent*) override;
    void paletteMousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void paletteMouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void paletteMouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
    void emitDrawingToolSelected() override;
};

} // namespace Graphic

} // namespace DrawingTool
