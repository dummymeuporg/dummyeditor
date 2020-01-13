#ifndef GRAPHICERASER_H
#define GRAPHICERASER_H

#include "drawingTool/graphicGeneralTool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
class VisibleGraphicLayer;
}

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  GraphicEraser class
//////////////////////////////////////////////////////////////////////////////

class GraphicEraser : public GraphicGeneralTool
{
    Q_OBJECT
public:
    GraphicEraser(GraphicMap::MapGraphicsScene&,
                  GraphicMap::VisibleGraphicLayer* = nullptr);
    void accept(DrawingVisitor&) override;
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
    bool m_mouseClicked;
};

} // namespace DrawingTools

#endif // GRAPHICERASER_H
