#ifndef GRAPHICERASER_H
#define GRAPHICERASER_H

#include "drawing_tool/graphic/graphic_tool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class VisibleGraphicLayer;
}


namespace DrawingTools {
namespace Graphic {

//////////////////////////////////////////////////////////////////////////////
//  GraphicEraser class
//////////////////////////////////////////////////////////////////////////////

class GraphicEraser : public GraphicTool {
    Q_OBJECT
public:
    GraphicEraser(
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
    bool m_mouseClicked;
};

} // namespace Graphic
} // namespace DrawingTools

#endif // GRAPHICERASER_H
