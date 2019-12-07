#pragma once

#include <QGraphicsRectItem>

#include "drawing_tool/graphic/graphic_tool.hpp"


namespace DrawingTool {

class Selection : public DrawingTool {
    Q_OBJECT
public:
    Selection(GraphicMap::MapGraphicsScene&);
    void accept(Visitor&) override;
    void mapMousePressEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(::QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(::QKeyEvent*) override;
    void mapKeyReleaseEvent(::QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void drawGrid() override;
    void onSelected() override;
    void onUnselected() override;
signals:
    void drawingToolSelected(::DrawingTool::DrawingTool*);
private:
    void drawSelection();
    bool m_mouseClicked;
    QGraphicsRectItem* m_selectionRectItem;
    QPoint m_startSelection, m_endSelection;
};

} // namespace DrawingTool
