#include "widget/drawing_toolbar/state/display_blocking_tools.hpp"

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

}

void
DisplayBlockingTools::visitGraphicLayer(
    GraphicMap::VisibleGraphicLayer& layer
) {
    // Here we will reset tools and change state.
}


} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
