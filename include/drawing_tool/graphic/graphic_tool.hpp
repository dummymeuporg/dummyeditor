#ifndef GRAPHICTOOL_H
#define GRAPHICTOOL_H

#include "drawing_tool/drawing_tool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace DrawingTools {
class Visitor;

//////////////////////////////////////////////////////////////////////////////
//  GraphicTool class
//////////////////////////////////////////////////////////////////////////////

class GraphicTool : public DrawingTool {
    Q_OBJECT
public:
    GraphicTool(
        QIcon&&,
        GraphicMap::MapGraphicsScene&,
        GraphicMap::VisibleGraphicLayer* = nullptr
    );
    void emitDrawingToolSelected() override;
    void drawGrid() override;
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer() const {
        return m_visibleGraphicLayer;
    }
    void setVisibleGraphicLayer(GraphicMap::VisibleGraphicLayer*);

    // Methods inherited from GraphicMap::GraphicLayerVisitor
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;

signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTools::GraphicTool*);

protected:
    GraphicMap::VisibleGraphicLayer* m_visibleGraphicLayer;
};

} // namespace DrawingTools

#endif
