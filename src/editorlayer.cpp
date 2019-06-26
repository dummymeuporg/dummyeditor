#include "editorlayer.hpp"

EditorLayer::EditorLayer(const Dummy::Core::GraphicLayer& graphicLayer)
    : m_layer(graphicLayer) {}

void EditorLayer::setVisible(bool visible) {
    m_visible = visible;
}
