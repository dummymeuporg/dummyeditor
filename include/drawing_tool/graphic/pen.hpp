#pragma once

#include "drawing_tool/graphic/palette_tool.hpp"

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class VisibleGraphicLayer;
}

namespace DrawingTool {

namespace Graphic {

class Pen : public PaletteTool {
    Q_OBJECT
public:
    Pen(GraphicMap::VisibleGraphicLayer&);
    void accept(Visitor&) override;
    void mapMousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(::QKeyEvent*) override;
    void mapKeyReleaseEvent(::QKeyEvent*) override;
    void emitDrawingToolSelected() override;
signals:
    void drawingToolSelected(::DrawingTool::DrawingTool*);
private:
    ::QGraphicsPixmapItem* m_hoverItem;
};

} // namespace Graphic

} // namespace DrawingTool
