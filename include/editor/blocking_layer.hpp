#ifndef BLOCKINGLAYER_H
#define BLOCKINGLAYER_H

#include <cstdint>
#include <vector>

#include "editor/layer.hpp"

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

namespace Dummy {
namespace Core {
class BlockingLayer;
} // namespace Core
} // namespace Dummy

namespace Editor {

//////////////////////////////////////////////////////////////////////////////
//  BlockingLayer class
//////////////////////////////////////////////////////////////////////////////

class BlockingLayer : public Layer {
public:
    BlockingLayer(Dummy::Core::BlockingLayer&);

    Dummy::Core::BlockingLayer& layer() { return m_layer; }
    std::uint8_t& operator[](std::size_t index);

    std::uint16_t width() const;
    std::uint16_t height() const;

private:
    Dummy::Core::BlockingLayer& m_layer;
};

} // namespace Editor

#endif // BLOCKINGLAYER_H
