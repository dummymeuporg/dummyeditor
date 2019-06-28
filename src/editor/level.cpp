#include "editor/level.hpp"
#include "editor/graphic_layer.hpp"

namespace Editor {
Level::Level(const Dummy::Core::MapLevel& mapLevel)
    : m_visible(true), m_mapLevel(mapLevel)
{
    for (const auto& [position, layer]: m_mapLevel.layers()) {
        m_graphicLayers[position] = std::make_unique<GraphicLayer>(layer);
    }
}

void
Level::setGraphicLayer(
    std::int8_t position,
    std::unique_ptr<GraphicLayer> layer)
{
    m_graphicLayers[position] = std::move(layer);
}

void Level::setVisible(bool visible) {
    m_visible = visible;
}
} // namespace Editor
