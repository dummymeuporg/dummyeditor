#ifndef DRAWINGTOOLVISITOR_H
#define DRAWINGTOOLVISITOR_H

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingTools {
class SelectionTool;

class BlockingEraser;
class BlockingPen;

class GraphicPen;
class GraphicRectangle;
class GraphicEraser;

//////////////////////////////////////////////////////////////////////////////
//  DrawingTools::Visitor interface
//////////////////////////////////////////////////////////////////////////////

class DrawingVisitor
{
public:
    virtual void visitTool(GraphicPen&)       = 0;
    virtual void visitTool(GraphicRectangle&) = 0;
    virtual void visitTool(GraphicEraser&)    = 0;
    virtual void visitTool(SelectionTool&)    = 0;
    virtual void visitTool(BlockingPen&)      = 0;
    virtual void visitTool(BlockingEraser&)   = 0;
};

} // namespace DrawingTools

#endif // DRAWINGTOOLVISITOR_H
