#ifndef BLOCKINGLAYER_H
#define BLOCKINGLAYER_H

#include <cstdint>
#include <vector>

#include "dummy/core/layer.hpp"
#include "editor/layer.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {

//////////////////////////////////////////////////////////////////////////////
//  BlockingLayer class
//////////////////////////////////////////////////////////////////////////////

class BlockingLayer : public Layer
{
public:
    explicit BlockingLayer(Dummy::Core::BlockingLayer&);

    Dummy::Core::BlockingLayer& layer() { return m_layer; }
    uint8_t at(tilecoords coords) { return m_layer.at(coords); }
    void set(tilecoords coords, uint8_t val) { m_layer.set(coords, val); }

    uint16_t width() const;
    uint16_t height() const;

private:
    Dummy::Core::BlockingLayer& m_layer;
};

} // namespace Editor

#endif // BLOCKINGLAYER_H
