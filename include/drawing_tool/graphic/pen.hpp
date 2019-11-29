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
    Pen(
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
    ::QGraphicsPixmapItem* m_hoverItem;
};

} // namespace Graphic

} // namespace DrawingTool
