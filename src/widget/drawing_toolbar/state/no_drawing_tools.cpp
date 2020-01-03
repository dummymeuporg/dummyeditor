#include "widget/drawing_toolbar/state/no_drawing_tools.hpp"

#include "widget/drawing_toolbar/state/display_blocking_tools.hpp"
#include "widget/drawing_toolbar/state/display_graphic_tools.hpp"
#include "widget/drawing_toolbar/widget.hpp"

namespace Widget {
namespace DrawingToolbar {
namespace State {

NoDrawingTools::NoDrawingTools(Widget& widget)
    : State(widget)
{}

void NoDrawingTools::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer) {
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayBlockingTools>(m_widget));
}

void NoDrawingTools::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    // Here we will reset tools and change state.
    auto self(shared_from_this());
    m_widget.reset();
    m_widget.setState(std::make_shared<DisplayGraphicTools>(m_widget));
}

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
