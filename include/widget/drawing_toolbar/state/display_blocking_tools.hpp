#ifndef DISPLAYBLOCKINGTOOLS_H
#define DISPLAYBLOCKINGTOOLS_H

#include "widget/drawing_toolbar/state/state.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Widget {
namespace DrawingToolbar {
namespace State {

//////////////////////////////////////////////////////////////////////////////
//  DisplayBlockingTools state
//////////////////////////////////////////////////////////////////////////////

class DisplayBlockingTools : public State {
public:
    DisplayBlockingTools(Widget&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
};

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget

#endif // DISPLAYBLOCKINGTOOLS_H
