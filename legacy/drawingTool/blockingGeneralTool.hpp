#ifndef BLOCKINGTOOL_H
#define BLOCKINGTOOL_H

#include "legacy/drawingTool/drawingTool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class BlockingGraphicLayer;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingVisitor;

//////////////////////////////////////////////////////////////////////////////
//  BlockingTool class
//////////////////////////////////////////////////////////////////////////////

class BlockingGeneralTool : public DrawingTool
{
    Q_OBJECT
public:
    BlockingGeneralTool(QIcon&&, GraphicMap::MapGraphicsScene& mapGraphicsScene,
                        GraphicMap::BlockingGraphicLayer* = nullptr);

    GraphicMap::BlockingGraphicLayer* blockingLayer();

    void emitDrawingToolSelected() override;
    void drawGrid() override;

    void setBlockingGraphicLayer(GraphicMap::BlockingGraphicLayer*);

    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::EventsGraphicLayer&) override;

signals:
    void drawingToolSelected(DrawingTools::BlockingGeneralTool*);

private:
    GraphicMap::BlockingGraphicLayer* m_blockingGraphicLayer = nullptr;
};

} // namespace DrawingTools

#endif
