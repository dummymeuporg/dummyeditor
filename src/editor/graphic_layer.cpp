#include "core/graphic_layer.hpp"
#include "editor/graphic_layer.hpp"

namespace Editor {

GraphicLayer::GraphicLayer(Dummy::Core::GraphicLayer& layer)
    : m_layer(layer) {}

std::pair<std::int8_t, std::int8_t>&
GraphicLayer::operator[](std::size_t index) {
    return m_layer[index];
}

std::uint16_t GraphicLayer::width() const {
    return m_layer.width();
}

std::uint16_t GraphicLayer::height() const {
    return m_layer.height();
}

} // namespace Editor
