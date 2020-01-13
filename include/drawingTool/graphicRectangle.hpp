#ifndef GRAPHICRECTANGLE_H
#define GRAPHICRECTANGLE_H

#include "drawingTool/graphicPaletteTool.hpp"

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  GraphicRectangle class
//////////////////////////////////////////////////////////////////////////////

class GraphicRectangle : public GraphicPaletteTool
{
    Q_OBJECT
public:
    GraphicRectangle(GraphicMap::MapGraphicsScene&,
                     GraphicMap::VisibleGraphicLayer* = nullptr);
    void accept(DrawingVisitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(QKeyEvent*) override;
    void mapKeyReleaseEvent(QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void onUnselected() override;

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    void drawHoverPreviewItem();
    void applyChipsetSelectionInRectangle();
    void applySelectionToMap(quint16 mapX, quint16 mapY);
    QRect adjustedRectFromP1P2(const QPoint& p1, const QPoint& p2);

private:
    bool m_mouseClicked = false;
    QPoint m_firstClickPos;
    QRect m_rectangle;
    // Rectangle Graphic Item to be drawn on the map edition.
    QGraphicsPixmapItem* m_hoverItem = nullptr;
};

} // namespace DrawingTools

#endif // GRAPHICRECTANGLE_H
