#ifndef BLOCKINGERASER_H
#define BLOCKINGERASER_H

#include "legacy/drawingTool/blockingGeneralTool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
class BlockingGraphicLayer;
}

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  BlockingEraser class
//////////////////////////////////////////////////////////////////////////////

class BlockingEraser : public BlockingGeneralTool
{
    Q_OBJECT
public:
    BlockingEraser(GraphicMap::MapGraphicsScene&,
                   GraphicMap::BlockingGraphicLayer* = nullptr);
    void accept(DrawingVisitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void emitDrawingToolSelected() override;

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    bool m_mouseClicked = false;
};

} // namespace DrawingTools

#endif // BLOCKINGERASER_H
