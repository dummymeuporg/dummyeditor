#ifndef DISPLAYGRAPHICTOOL_H
#define DISPLAYGRAPHICTOOL_H

#include "widget/drawing_toolbar/state/state.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Widget {
namespace DrawingToolbar {
namespace State {

//////////////////////////////////////////////////////////////////////////////
//  DrawingToolAction state
//////////////////////////////////////////////////////////////////////////////

class DisplayGraphicTools : public State {
public:
    DisplayGraphicTools(Widget&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&layer) override;
};

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget

#endif // DISPLAYGRAPHICTOOL_H
