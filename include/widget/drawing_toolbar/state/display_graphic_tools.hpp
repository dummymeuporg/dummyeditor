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

class DisplayGraphicTools : public State {
public:
    DisplayGraphicTools(Widget&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&layer) override;
};

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
