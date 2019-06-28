#include "editor/layer.hpp"

namespace Editor {
Layer::Layer(const Dummy::Core::GraphicLayer& graphicLayer)
    : m_layer(graphicLayer) {}

void Layer::setVisible(bool visible) {
    m_visible = visible;
}

} // namespace Editor
