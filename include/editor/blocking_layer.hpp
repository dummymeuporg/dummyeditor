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
private:
    Dummy::Core::BlockingLayer& m_layer;
};

} // namespace Editor
