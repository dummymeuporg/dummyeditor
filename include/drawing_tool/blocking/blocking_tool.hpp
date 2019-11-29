#pragma once

#include <QRect>
#include "drawing_tool/drawing_tool.hpp"

namespace GraphicMap {
class BlockingGraphicLayer;
} // namespace GraphicMap

namespace DrawingTool {

class Visitor;

namespace Blocking {

class BlockingTool : public DrawingTool {
    Q_OBJECT
public:
    BlockingTool(
        QIcon&&,
        GraphicMap::MapGraphicsScene& mapGraphicsScene,
        GraphicMap::BlockingGraphicLayer* = nullptr
    );
    void emitDrawingToolSelected() override;
    void drawGrid() override;
    void setBlockingGraphicLayer(GraphicMap::BlockingGraphicLayer*);

    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;

signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTool::Blocking::BlockingTool*);
protected:
    GraphicMap::BlockingGraphicLayer* m_blockingGraphicLayer;
};

} // namespace Graphic
} // namespace DrawingTool
