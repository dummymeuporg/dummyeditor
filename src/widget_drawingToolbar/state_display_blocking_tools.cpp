#include "drawingTool/blockingGeneralTool.hpp"

#include "graphicMap/mapGraphicsScene.hpp"

#include "widget_drawingToolbar/state_display_blocking_tools.hpp"
#include "widget_drawingToolbar/state_display_graphic_tools.hpp"

namespace DrawingToolbar {

DisplayBlockingToolState::DisplayBlockingToolState(Widget& widget)
    : State(widget)
{}

void DisplayBlockingToolState::visitGraphicLayer(
    GraphicMap::BlockingGraphicLayer& layer)
{
    auto tool = m_widget.mapScene()->drawingTool();
    if (nullptr != tool) {
        reinterpret_cast<DrawingTools::BlockingGeneralTool*>(tool)
            ->setBlockingGraphicLayer(&layer);
    }
}

void DisplayBlockingToolState::visitGraphicLayer(
    GraphicMap::VisibleGraphicLayer&)
{
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayGraphicToolState>(m_widget));
}

} // namespace DrawingToolbar
