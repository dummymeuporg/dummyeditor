#include "drawing_tool/graphic/graphic_tool.hpp"

#include "graphicmap/mapgraphicsscene.hpp"

#include "widget/drawing_toolbar/widget.hpp"
#include "widget/drawing_toolbar/state/display_blocking_tools.hpp"
#include "widget/drawing_toolbar/state/display_graphic_tools.hpp"

namespace Widget {
namespace DrawingToolbar {
namespace State {

DisplayGraphicTools::DisplayGraphicTools(Widget& widget)
    : State(widget)
{}

void
DisplayGraphicTools::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer)
{
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayBlockingTools>(m_widget));
}

void
DisplayGraphicTools::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer)
{
    // Nothing to do here. We are already displaying accurate tools.

    // XXX: Disgusting.
    reinterpret_cast<DrawingTool::Graphic::GraphicTool*>(
        m_widget.mapScene()->drawingTool()
    )->setVisibleGraphicLayer(&layer);
}

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
