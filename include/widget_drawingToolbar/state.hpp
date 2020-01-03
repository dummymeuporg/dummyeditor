#ifndef DRAWINGTOOLBARSTATE_H
#define DRAWINGTOOLBARSTATE_H

#include <memory>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class BlockingGraphicLayer;
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace DrawingToolbar {
class Widget;

//////////////////////////////////////////////////////////////////////////////
//  State class
//////////////////////////////////////////////////////////////////////////////

class State : public std::enable_shared_from_this<State> {
public:
    State(Widget&);
    virtual void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) = 0;
    virtual void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) = 0;
protected:
    Widget& m_widget;
};

} // namespace DrawingToolbar

#endif // DRAWINGTOOLBARSTATE_H
