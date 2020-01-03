#include "widget/drawing_toolbar/drawing_tool_action.hpp"

#include "drawing_tool/drawing_tool.hpp"

namespace Widget {
namespace DrawingToolbar {

DrawingToolAction::DrawingToolAction(
    DrawingTools::DrawingTool* drawingTool,
    QWidget* parent)
    : QAction(parent)
    , m_drawingTool(drawingTool)
{}

void DrawingToolAction::setDrawingTool(bool checked) {
    if (checked) {
        // Forward the drawing tool.
        m_drawingTool->emitDrawingToolSelected();
    }
}

} // namespace DrawingToolbar
} // namespace Widget
