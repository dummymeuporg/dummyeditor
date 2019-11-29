#pragma once

#include <memory>

namespace GraphicMap {
class BlockingGraphicLayer;
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace Widget {
namespace DrawingToolbar {
class Widget;
namespace State {

class State : public std::enable_shared_from_this<State> {
public:
    State(Widget&);
    virtual void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) = 0;
    virtual void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) = 0;
protected:
    Widget& m_widget;
};

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
