#include "local/level.hpp"

#include "editor/level.hpp"
#include "editor/blocking_layer.hpp"
#include "editor/graphic_layer.hpp"

namespace Editor {
Level::Level(const Dummy::Local::Level& level)
    : m_visible(true),
      m_level(level),
      m_blockingLayer(std::make_unique<BlockingLayer>(m_level.blockingLayer()))
{
    for (const auto& [position, layer]: m_level.graphicLayers()) {
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
