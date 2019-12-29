#ifndef BLOCKING_H
#define BLOCKING_H

#include "drawing_tool/blocking/blocking_tool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
class BlockingGraphicLayer;
}

namespace DrawingTools {
namespace Blocking {

//////////////////////////////////////////////////////////////////////////////
//  BlockingPen class
//////////////////////////////////////////////////////////////////////////////

class BlockingPen : public BlockingTool {
    Q_OBJECT
public:
    BlockingPen(
        GraphicMap::MapGraphicsScene&,
        GraphicMap::BlockingGraphicLayer* = nullptr
    );
    void accept(Visitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(QKeyEvent*) override;
    void mapKeyReleaseEvent(QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void onUnselected() override;
    void onSelected() override;

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    bool m_mouseClicked;
};

} // namespace Blocking
} // namespace DrawingTools

#endif // BLOCKING_H
