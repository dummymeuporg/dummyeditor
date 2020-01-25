#ifndef GRAPHICTOOL_H
#define GRAPHICTOOL_H

#include "legacy/drawingTool/drawingTool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingVisitor;

//////////////////////////////////////////////////////////////////////////////
//  GraphicTool class
//////////////////////////////////////////////////////////////////////////////

class GraphicGeneralTool : public DrawingTool
{
    Q_OBJECT
public:
    GraphicGeneralTool(QIcon&&, GraphicMap::MapGraphicsScene&,
                       GraphicMap::VisibleGraphicLayer* = nullptr);
    void emitDrawingToolSelected() override;
    void drawGrid() override;
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer() const
    {
        return m_visibleGraphicLayer;
    }
    void setVisibleGraphicLayer(GraphicMap::VisibleGraphicLayer*);

    // Methods inherited from GraphicMap::GraphicLayerVisitor
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::EventsGraphicLayer&) override;

signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTools::GraphicGeneralTool*);

protected:
    GraphicMap::VisibleGraphicLayer* visibleGraphicLayer();

private:
    GraphicMap::VisibleGraphicLayer* m_visibleGraphicLayer = nullptr;
};

} // namespace DrawingTools

#endif
