#ifndef BLOCKINGTOOL_H
#define BLOCKINGTOOL_H

#include "drawingTool/drawingTool.hpp"

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
    void emitDrawingToolSelected() override;
    void drawGrid() override;
    void setBlockingGraphicLayer(GraphicMap::BlockingGraphicLayer*);

    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;

signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    // TODO check if it's still the case now that the namespace has not the
    // same name as the class
    void drawingToolSelected(DrawingTools::BlockingGeneralTool*);

protected:
    GraphicMap::BlockingGraphicLayer* m_blockingGraphicLayer;
};

} // namespace DrawingTools

#endif
