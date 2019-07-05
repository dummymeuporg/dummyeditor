#include "graphicmap/visiblegraphiclayer.hpp"
#include "drawing_tool/graphic/graphic_tool.hpp"

namespace DrawingTool {
namespace Graphic {

GraphicTool::GraphicTool(
        QIcon&& icon,
        GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : DrawingTool(std::move(icon)), m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicTool::setChipsetSelection(QRect rect) {
    m_chipsetSelection = rect;
}

} // namespace Graphic
} // namespace DrawingTool
