#include "drawing_tool/blocking/blocking_tool.hpp"

#include "graphicmap/mapgraphicsscene.hpp"

#include "widget/drawing_toolbar/widget.hpp"

#include "widget/drawing_toolbar/state/display_blocking_tools.hpp"
#include "widget/drawing_toolbar/state/display_graphic_tools.hpp"


namespace Widget {
namespace DrawingToolbar {
namespace State {

DisplayBlockingTools::DisplayBlockingTools(Widget& widget)
    : State(widget)
{}

void
DisplayBlockingTools::visitGraphicLayer(
    GraphicMap::BlockingGraphicLayer& layer
) {
    auto tool = m_widget.mapScene()->drawingTool();
    if (nullptr != tool) {
        reinterpret_cast<DrawingTool::Blocking::BlockingTool*>(
            tool
        )->setBlockingGraphicLayer(&layer);
    }
}

void
DisplayBlockingTools::visitGraphicLayer(
    GraphicMap::VisibleGraphicLayer&
) {
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayGraphicTools>(m_widget));
}


} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
