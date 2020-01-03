#ifndef NODRAWINGTOOLS_H
#define NODRAWINGTOOLS_H

#include "widget/drawing_toolbar/state/state.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Widget {
namespace DrawingToolbar {
namespace State {

//////////////////////////////////////////////////////////////////////////////
//  NoDrawingTools state
//////////////////////////////////////////////////////////////////////////////

class NoDrawingTools : public State {
public:
    NoDrawingTools(Widget&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
};

} // namespace State
} // namespace DrawingToolbar
} // namespace Widget

#endif // NODRAWINGTOOLS_H
