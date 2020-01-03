#ifndef DISPLAYBLOCKINGTOOLS_H
#define DISPLAYBLOCKINGTOOLS_H

#include "widget/drawing_toolbar/state/state.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingToolbar {

//////////////////////////////////////////////////////////////////////////////
//  DisplayBlockingTools state
//////////////////////////////////////////////////////////////////////////////

class DisplayBlockingToolState : public State {
public:
    DisplayBlockingToolState(Widget&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
};

} // namespace DrawingToolbar

#endif // DISPLAYBLOCKINGTOOLS_H
