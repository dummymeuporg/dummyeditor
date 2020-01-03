#ifndef BLOCKINGERASER_H
#define BLOCKINGERASER_H

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
//  BlockingEraser class
//////////////////////////////////////////////////////////////////////////////

class BlockingEraser : public BlockingGeneralTool {
    Q_OBJECT
public:
    BlockingEraser(GraphicMap::MapGraphicsScene&,
           GraphicMap::BlockingGraphicLayer* = nullptr);
    void accept(DrawingVisitor&) override;
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

} // namespace DrawingTools

#endif // BLOCKINGERASER_H
