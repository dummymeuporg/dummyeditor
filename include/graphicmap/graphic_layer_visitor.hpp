#ifndef GRAPHICLAYERVISITOR_H
#define GRAPHICLAYERVISITOR_H

#include <exception>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {

class BlockingGraphicLayer;
class EventsGraphicLayer;
class VisibleGraphicLayer;

//////////////////////////////////////////////////////////////////////////////
//  Exceptions
//////////////////////////////////////////////////////////////////////////////

class GraphicLayerNotSupported : public std::exception {
public:
    const char* what() const noexcept override {
        return "this graphic layer is not supported";
    }
};

//////////////////////////////////////////////////////////////////////////////
//  GraphicLayerVisitor interface
//////////////////////////////////////////////////////////////////////////////

class GraphicLayerVisitor {
public:
    virtual void visitGraphicLayer(VisibleGraphicLayer&) {
        throw GraphicLayerNotSupported();
    }

    virtual void visitGraphicLayer(BlockingGraphicLayer&) {
        throw GraphicLayerNotSupported();
    }

    virtual void visitGraphicLayer(EventsGraphicLayer&) {
        throw GraphicLayerNotSupported();
    }
};

}

#endif // GRAPHICLAYERVISITOR_H
