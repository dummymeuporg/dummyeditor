#pragma once

namespace DrawingTool {

namespace Blocking {
class Pen;
} // namespace Blocking
namespace Graphic {
class Pen;
class Rectangle;
class Eraser;
} // namespace Graphic

class Visitor {
public:
    virtual void visitTool(Graphic::Pen&) = 0;
    virtual void visitTool(Graphic::Rectangle&) = 0;
    virtual void visitTool(Graphic::Eraser&) = 0;
    virtual void visitTool(Blocking::Pen&) = 0;
};

} // namespace DrawingTool
