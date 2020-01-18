#include "drawingTool/drawingTool.hpp"

namespace DrawingTools {

DrawingTool::DrawingTool(GraphicMap::MapGraphicsScene& mapGraphicsScene,
                         QIcon&& icon)
    : m_mapGraphicsScene(mapGraphicsScene)
    , m_icon(std::move(icon))
{}

void DrawingTool::emitDrawingToolSelected()
{
    emit drawingToolSelected(this);
}

void DrawingTool::onSelected()
{
    /* default : do nothing */
}

void DrawingTool::onUnselected()
{
    /* default : do nothing */
}

void DrawingTool::setSelected(bool selected)
{
    if (selected) {
        emitDrawingToolSelected();
    }
}

} // namespace DrawingTools
