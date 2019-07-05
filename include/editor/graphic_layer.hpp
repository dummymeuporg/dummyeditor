
#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
class GraphicLayer;
} // namespace Core
} // namespace Dummy

#include "editor/layer.hpp"

namespace Editor {

class GraphicLayer : public Layer {
public:
    GraphicLayer(Dummy::Core::GraphicLayer&);
    Dummy::Core::GraphicLayer& layer() {
        return m_layer;
    }

    std::pair<std::int8_t, std::int8_t>& operator[](std::size_t index);

    std::uint16_t width() const;
    std::uint16_t height() const;

private:
    Dummy::Core::GraphicLayer& m_layer;

};

} // namespace Editor
