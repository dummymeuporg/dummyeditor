#include "drawing_tool/blocking/blocking_tool.hpp"

#include "graphicmap/mapgraphicsscene.hpp"

#include "widget/drawing_toolbar/state/display_blocking_tools.hpp"
#include "widget/drawing_toolbar/state/display_graphic_tools.hpp"

namespace DrawingToolbar {

DisplayBlockingToolState::DisplayBlockingToolState(Widget& widget)
    : State(widget)
{}

void DisplayBlockingToolState::visitGraphicLayer(
    GraphicMap::BlockingGraphicLayer& layer
) {
    auto tool = m_widget.mapScene()->drawingTool();
    if (nullptr != tool) {
        reinterpret_cast<DrawingTools::BlockingTool*>(
            tool
        )->setBlockingGraphicLayer(&layer);
    }
}

void DisplayBlockingToolState::visitGraphicLayer(GraphicMap::VisibleGraphicLayer&){
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayGraphicToolState>(m_widget));
}

} // namespace DrawingToolbar
