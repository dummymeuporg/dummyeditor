#pragma once

namespace DrawingTool {

namespace Graphic {
class Pen;
} // namespace Graphic

class Visitor {
public:
    virtual void visitTool(Graphic::Pen&) = 0;
};

} // namespace DrawingTool
