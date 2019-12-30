#ifndef GRAPHICRECTANGLE_H
#define GRAPHICRECTANGLE_H

#include "drawing_tool/graphic/palette_tool.hpp"

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  GraphicRectangle class
//////////////////////////////////////////////////////////////////////////////

class GraphicRectangle : public GraphicPaletteTool {
    Q_OBJECT
public:
    GraphicRectangle(GraphicMap::MapGraphicsScene&,
              GraphicMap::VisibleGraphicLayer* = nullptr);
    void accept(Visitor&) override;
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
    void drawChipsetSelectionInRectangle();
    void applyChipsetSelectionInRectangle();
    void applySelectionToMap(quint16 mapX, quint16 mapY);

private:
    bool m_mouseClicked;
    QRect m_rectangle;
    // Rectangle Graphic Item to be drawn on the map edition.
    QGraphicsPixmapItem* m_hoverItem;
};

} // namespace DrawingTools

#endif // GRAPHICRECTANGLE_H
