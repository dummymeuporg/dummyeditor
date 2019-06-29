#include "editor/level.hpp"
#include "editor/blocking_layer.hpp"
#include "editor/graphic_layer.hpp"

namespace Editor {
Level::Level(const Dummy::Core::MapLevel& mapLevel)
    : m_visible(true),
      m_mapLevel(mapLevel),
      m_blockingLayer(
          std::make_unique<BlockingLayer>(
              m_mapLevel.blockingLayer()
          )
      )
{
    for (const auto& [position, layer]: m_mapLevel.graphicLayers()) {
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
