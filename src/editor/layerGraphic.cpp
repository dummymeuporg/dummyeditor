#include "editor/layerGraphic.hpp"

#include <dummy/core/layer.hpp>

namespace Editor {

GraphicLayer::GraphicLayer(Dummy::Core::GraphicLayer& layer)
    : m_layer(layer)
{}

uint16_t GraphicLayer::width() const
{
    return m_layer.width();
}

uint16_t GraphicLayer::height() const
{
    return m_layer.height();
}

} // namespace Editor
