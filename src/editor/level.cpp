#include "editor/layer.hpp"
#include "editor/level.hpp"

namespace Editor {
Level::Level(const Dummy::Core::MapLevel& mapLevel)
    : m_visible(true), m_mapLevel(mapLevel)
{
    for (const auto& [position, layer]: m_mapLevel.layers()) {
        m_editorLayers[position] = std::make_unique<Layer>(layer);
    }
}

void
Level::setLayer(
    std::int8_t position,
    std::unique_ptr<Layer> layer
) {
    m_editorLayers[position] = std::move(layer);
}

void Level::setVisible(bool visible) {
    m_visible = visible;
}
} // namespace Editor