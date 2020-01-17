#ifndef GRAPHICPEN_H
#define GRAPHICPEN_H

#include "drawingTool/graphicPaletteTool.hpp"

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  GraphicPen class
//////////////////////////////////////////////////////////////////////////////

class GraphicPen : public GraphicPaletteTool
{
    Q_OBJECT
public:
    GraphicPen(GraphicMap::MapGraphicsScene&,
               GraphicMap::VisibleGraphicLayer* = nullptr);
    void accept(DrawingVisitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void emitDrawingToolSelected() override;
    void onSelected() override;
    void onUnselected() override;

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    void drawPattern(const QGraphicsSceneMouseEvent*);

    QGraphicsPixmapItem* m_hoverItem = nullptr;
    bool m_mousePressed              = false;
};

} // namespace DrawingTools

#endif // GRAPHICPEN_H
