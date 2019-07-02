#include "core/blocking_layer.hpp"
#include "core/graphic_layer.hpp"

#include "local/level.hpp"

#include "editor/blocking_layer.hpp"
#include "editor/graphic_layer.hpp"
#include "editor/level.hpp"

namespace Editor {
Level::Level(Dummy::Local::Level& level)
    : m_level(level),
      m_blockingLayer(nullptr),
      m_visible(true)
{
    // XXX: create blocking layer and graphic layers
    m_blockingLayer = std::make_unique<BlockingLayer>(m_level.blockingLayer());

    for (auto& [position, layer]: m_level.graphicLayers()) {
        m_graphicLayers[position] = std::make_unique<GraphicLayer>(layer);
    }
}

void Level::setVisible(bool visible) {
    m_visible = visible;
}

} // namespace Editor
