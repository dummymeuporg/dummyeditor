#include "widget/drawing_toolbar/drawing_tool_action.hpp"

namespace Widget {
namespace DrawingToolbar {

DrawingToolAction::DrawingToolAction(
    DrawingTool::DrawingTool* drawingTool,
    QWidget* parent
) : QAction(parent), m_drawingTool(drawingTool)
{}

void DrawingToolAction::setDrawingTool(bool checked) {
    if (checked) {
        // Forward the drawing tool.
        emit trigerred(m_drawingTool);
    }
}

} // namespace DrawingToolbar
} // namespace Widget
