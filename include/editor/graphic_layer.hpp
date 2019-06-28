#pragma once

#include <cstdint>
#include <vector>


#include "editor/layer.hpp"

namespace Dummy {
namespace Core {
using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;
} // namespace Core
} // namespace Dummy

namespace Editor {
class GraphicLayer : public Layer {
public:
    GraphicLayer(const Dummy::Core::GraphicLayer&);
private:
    const Dummy::Core::GraphicLayer& m_layer;
};
} // namespace Editor
