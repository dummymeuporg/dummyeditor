#pragma once

#include <cstdint>
#include <vector>


#include "editor/layer.hpp"

namespace Dummy {
namespace Core {
using BlockingLayer = std::vector<std::uint8_t>;
} // namespace Core
} // namespace Dummy

namespace Editor {
class BlockingLayer : public Layer {
public:
    BlockingLayer(const Dummy::Core::BlockingLayer&);
private:
    const Dummy::Core::BlockingLayer& m_layer;
};
} // namespace Editor
