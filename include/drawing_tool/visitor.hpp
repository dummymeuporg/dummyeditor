#ifndef DRAWINGTOOLVISITOR_H
#define DRAWINGTOOLVISITOR_H

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingTools {
class Selection;

namespace Blocking {
class BlockingEraser;
class BlockingPen;
} // namespace Blocking

namespace Graphic {
class GraphicPen;
class GraphicRectangle;
class GraphicEraser;
class Selection;
} // namespace Graphic

//////////////////////////////////////////////////////////////////////////////
//  DrawingTools::Visitor interface
//////////////////////////////////////////////////////////////////////////////

class Visitor {
public:
    virtual void visitTool(Graphic::GraphicPen&) = 0;
    virtual void visitTool(Graphic::GraphicRectangle&) = 0;
    virtual void visitTool(Graphic::GraphicEraser&) = 0;
    virtual void visitTool(Selection&) = 0;
    virtual void visitTool(Blocking::BlockingPen&) = 0;
    virtual void visitTool(Blocking::BlockingEraser&) = 0;
};

} // namespace DrawingTool

#endif DRAWINGTOOLVISITOR_H
