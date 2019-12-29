#ifndef GRAPHICPEN_H
#define GRAPHICPEN_H

#include "drawing_tool/graphic/palette_tool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  GraphicTool class
//////////////////////////////////////////////////////////////////////////////

class GraphicPen : public GraphicPaletteTool {
    Q_OBJECT
public:
    GraphicPen(
        GraphicMap::MapGraphicsScene&,
        GraphicMap::VisibleGraphicLayer* = nullptr
    );
    void accept(Visitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(QKeyEvent*) override;
    void mapKeyReleaseEvent(QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void onSelected() override;
    void onUnselected() override;

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    void drawPattern(QGraphicsSceneMouseEvent*);
    QGraphicsPixmapItem* m_hoverItem;
    bool m_mousePressed;
};

} // namespace DrawingTools

#endif // GRAPHICPEN_H
