#include "widget_drawingToolbar/drawing_tool_action.hpp"

#include "drawingTool/drawingTool.hpp"

namespace DrawingToolbar {

DrawingToolAction::DrawingToolAction(DrawingTools::DrawingTool* drawingTool,
                                     QWidget* parent)
    : QAction(parent)
    , m_drawingTool(drawingTool)
{}

void DrawingToolAction::setDrawingTool(bool checked)
{
    if (checked) {
        // Forward the drawing tool.
        m_drawingTool->emitDrawingToolSelected();
    }
}

} // namespace DrawingToolbar
