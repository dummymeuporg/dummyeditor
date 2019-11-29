#pragma once

#include "widget/drawing_toolbar/state/state.hpp"

namespace GraphicMap {
class BlockingGraphicLayer;
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace Widget {
namespace DrawingToolbar {
class Widget;
namespace State {

class NoDrawingTools : public State {
public:
    NoDrawingTools(Widget&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
};

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
