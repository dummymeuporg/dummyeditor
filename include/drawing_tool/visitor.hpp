#pragma once

namespace DrawingTool {

namespace Graphic {
class Pen;
class Rectangle;
} // namespace Graphic

class Visitor {
public:
    virtual void visitTool(Graphic::Pen&) = 0;
    virtual void visitTool(Graphic::Rectangle&) = 0;
};

} // namespace DrawingTool
