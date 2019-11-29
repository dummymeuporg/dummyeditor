#pragma once

#include "drawing_tool/graphic/graphic_tool.hpp"

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class VisibleGraphicLayer;
}


namespace DrawingTool {
namespace Graphic {

class Eraser : public GraphicTool {
    Q_OBJECT
public:
    Eraser(
            GraphicMap::MapGraphicsScene&,
            GraphicMap::VisibleGraphicLayer* = nullptr
    );
    void accept(Visitor&) override;
    void mapMousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(::QKeyEvent*) override;
    void mapKeyReleaseEvent(::QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void onSelected() override;
    void onUnselected() override;
signals:
    void drawingToolSelected(::DrawingTool::DrawingTool*);
private:
    bool m_mouseClicked;
};

} // namespace Graphic
} // namespace DrawingTool
