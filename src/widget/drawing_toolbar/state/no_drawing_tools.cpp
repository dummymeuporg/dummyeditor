#include "widget/drawing_toolbar/state/no_drawing_tools.hpp"

#include "widget/drawing_toolbar/state/display_blocking_tools.hpp"
#include "widget/drawing_toolbar/state/display_graphic_tools.hpp"
#include "widget/drawing_toolbar/widget.hpp"

namespace DrawingToolbar {

NoDrawingToolState::NoDrawingToolState(Widget& widget)
    : State(widget)
{}

void NoDrawingToolState::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayBlockingToolState>(m_widget));
}

void NoDrawingToolState::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayGraphicToolState>(m_widget));
}

} // namespace DrawingToolbar
