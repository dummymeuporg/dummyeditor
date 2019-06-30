#include "core/blocking_layer.hpp"
#include "editor/blocking_layer.hpp"

namespace Editor {

BlockingLayer::BlockingLayer(Dummy::Core::BlockingLayer& layer)
    : m_layer(layer)
{}

std::uint8_t& BlockingLayer::operator[](std::size_t index) {
    return m_layer[index];
}

} // namespace Editor
