#include "editorlayer.hpp"
#include "editorlevel.hpp"

EditorLevel::EditorLevel(const Dummy::Core::MapLevel& mapLevel)
    : m_visible(true), m_mapLevel(mapLevel)
{
    for (const auto& [position, layer]: m_mapLevel.layers()) {
        m_editorLayers[position] = std::make_unique<EditorLayer>(layer);
    }
}

void
EditorLevel::setLayer(
    std::int8_t position,
    std::unique_ptr<EditorLayer> editorLayer
) {
    m_editorLayers[position] = std::move(editorLayer);
}
