#pragma once

#include "drawing_tool/blocking/blocking_tool.hpp"

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class BlockingGraphicLayer;
}

namespace DrawingTool {
namespace Blocking {

class Pen : public BlockingTool {
    Q_OBJECT
public:
    Pen(GraphicMap::BlockingGraphicLayer&);
    void accept(Visitor&) override;
    void mapMousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(::QKeyEvent*) override;
    void mapKeyReleaseEvent(::QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void onUnselected() override;
    void onSelected() override;
signals:
    void drawingToolSelected(::DrawingTool::DrawingTool*);
private:
    bool m_mouseClicked;
};

} // namespace Blocking
} // namespace DrawingTool
