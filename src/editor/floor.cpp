#include <dummy/core/blocking_layer.hpp>
#include <dummy/core/graphic_layer.hpp>

#include <dummy/local/floor.hpp>

#include "editor/blocking_layer.hpp"
#include "editor/graphic_layer.hpp"
#include "editor/floor.hpp"

namespace Editor {
Floor::Floor(Dummy::Local::Floor& floor)
    : m_floor(floor),
      m_blockingLayer(nullptr),
      m_visible(true)
{
    // XXX: create blocking layer and graphic layers
    m_blockingLayer = std::make_unique<BlockingLayer>(m_floor.blockingLayer());

    for (auto& [position, layer]: m_floor.graphicLayers()) {
        m_graphicLayers[position] = std::make_unique<GraphicLayer>(layer);
    }
}

void Floor::setVisible(bool visible) {
    m_visible = visible;
}

} // namespace Editor
