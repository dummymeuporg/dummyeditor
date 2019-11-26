#pragma once

#include <exception>

namespace GraphicMap {

class VisibleGraphicLayer;
class BlockingGraphicLayer;

class GraphicLayerNotSupportedException : public std::exception {
public:
    const char* what() const override {
        return "this graphic layer is not supported";
    }
};

class GraphicLayerVisitor {
public:
    virtual void visitGraphicLayer(VisibleGraphicLayer&) {
        throw GraphicLayerNotSupportedException();
    }

    virtual void visitGraphicLayer(BlockingGraphicLayer&) {
        throw GraphicLayerNotSupportedException();
    }
};

}
