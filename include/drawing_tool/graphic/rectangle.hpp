#pragma once

#include "drawing_tool/graphic/palette_tool.hpp"

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class VisibleGraphicLayer;
}

namespace DrawingTool {

namespace Graphic {

class Rectangle : public PaletteTool {
    Q_OBJECT
public:
    Rectangle(GraphicMap::VisibleGraphicLayer&);
    void accept(Visitor&) override;
    void mapMousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(::QKeyEvent*) override;
    void mapKeyReleaseEvent(::QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void onUnselected() override;
signals:
    void drawingToolSelected(::DrawingTool::DrawingTool*);
};

} // namespace Graphic

} // namespace DrawingTool
