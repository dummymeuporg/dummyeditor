#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
class BlockingLayer;
} // namespace Core
} // namespace Dummy

#include "editor/layer.hpp"

namespace Editor {

class BlockingLayer : public Layer {
public:
    BlockingLayer(Dummy::Core::BlockingLayer&);
    Dummy::Core::BlockingLayer& layer() {
        return m_layer;
    }
    std::uint8_t& operator[](std::size_t index);
private:
    Dummy::Core::BlockingLayer& m_layer;
};

} // namespace Editor
