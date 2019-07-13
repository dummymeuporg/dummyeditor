#pragma once

#include <QRect>
#include "drawing_tool/drawing_tool.hpp"

namespace GraphicMap {
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace DrawingTool {

class Visitor;

namespace Graphic {

class GraphicTool : public DrawingTool {
    Q_OBJECT
public:
    GraphicTool(QIcon&&, GraphicMap::VisibleGraphicLayer&);
    void emitDrawingToolSelected() override;
    void drawGrid() override;
signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTool::Graphic::GraphicTool*);
protected:
    GraphicMap::VisibleGraphicLayer& m_visibleGraphicLayer;
};


} // namespace Graphic

} // namespace DrawingTool
