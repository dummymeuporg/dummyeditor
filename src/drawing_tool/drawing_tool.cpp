#include "graphicmap/mapgraphicsscene.hpp"
#include "drawing_tool/drawing_tool.hpp"

namespace DrawingTool {

DrawingTool::DrawingTool(
    GraphicMap::MapGraphicsScene& mapGraphicsScene,
        QIcon&& icon
) : m_mapGraphicsScene(mapGraphicsScene), m_icon(std::move(icon))
{}

} // namespace DrawingTool
