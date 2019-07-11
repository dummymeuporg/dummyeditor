#pragma once

#include <QRect>

#include "drawing_tool/graphic/palette_tool.hpp"

class QGraphicsPixmapItem;
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
private:
    /* Methods. */
    void drawChipsetSelectionInRectangle();

    /* Attributes */
    bool b_mouseClicked;
    ::QRect m_rectangle;
    // Rectangle Graphic Item to be drawn on the map edition.
    ::QGraphicsPixmapItem* m_selectionItem;
};

} // namespace Graphic

} // namespace DrawingTool
