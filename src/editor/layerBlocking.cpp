#include "editor/layerBlocking.hpp"

#include <dummy/core/blocking_layer.hpp>

namespace Editor {

BlockingLayer::BlockingLayer(Dummy::Core::BlockingLayer& layer)
    : m_layer(layer)
{}

std::uint8_t& BlockingLayer::operator[](std::size_t index)
{
    return m_layer[index];
}

std::uint16_t BlockingLayer::width() const
{
    return m_layer.width();
}

std::uint16_t BlockingLayer::height() const
{
    return m_layer.height();
}

} // namespace Editor
