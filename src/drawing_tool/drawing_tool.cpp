#include "drawing_tool/drawing_tool.hpp"

namespace DrawingTool {

DrawingTool::DrawingTool(QIcon&& icon) : m_icon(std::move(icon))
{}

} // namespace DrawingTool
