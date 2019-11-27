#pragma once

#include <memory>

namespace Widget {
namespace DrawingToolbar {
class Widget;
namespace State {

class State : public std::enable_shared_from_this<State> {
public:
    State(Widget&);
protected:
    Widget& m_widget;
};

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget
