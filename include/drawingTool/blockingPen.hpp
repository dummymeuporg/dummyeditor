#ifndef BLOCKING_H
#define BLOCKING_H

#include "drawingTool/blockingGeneralTool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
class BlockingGraphicLayer;
}

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  BlockingPen class
//////////////////////////////////////////////////////////////////////////////

class BlockingPen : public BlockingGeneralTool
{
    Q_OBJECT
public:
    BlockingPen(GraphicMap::MapGraphicsScene&,
                GraphicMap::BlockingGraphicLayer* = nullptr);
    void accept(DrawingVisitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void emitDrawingToolSelected() override;
    void onUnselected() override;
    void onSelected() override;

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    bool m_mouseClicked = false;
};

} // namespace DrawingTools

#endif // BLOCKING_H
