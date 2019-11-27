#pragma once

#include <exception>

namespace GraphicMap {

class BlockingGraphicLayer;
class EventsGraphicLayer;
class VisibleGraphicLayer;

class GraphicLayerNotSupported : public std::exception {
public:
    const char* what() const override {
        return "this graphic layer is not supported";
    }
};

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
