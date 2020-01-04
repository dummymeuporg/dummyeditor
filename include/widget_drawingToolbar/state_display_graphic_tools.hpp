#ifndef DISPLAYGRAPHICTOOL_H
#define DISPLAYGRAPHICTOOL_H

#include "widget_drawingToolbar/state.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingToolbar {

//////////////////////////////////////////////////////////////////////////////
//  DrawingToolAction state
//////////////////////////////////////////////////////////////////////////////

class DisplayGraphicToolState : public State
{
public:
    DisplayGraphicToolState(Widget&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) override;
};

} // namespace DrawingToolbar

#endif // DISPLAYGRAPHICTOOL_H
