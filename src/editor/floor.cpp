#include "editor/floor.hpp"

#include <dummy/local/floor.hpp>


namespace Editor {

Floor::Floor(Dummy::Local::Floor& floor)
    : m_floor(floor)
    , m_blockingLayer(m_floor.blockingLayer())
    , m_eventsLayer(m_floor)
{
    for (auto& [position, layer] : m_floor.graphicLayers()) {
        // TODO same here, make_unique takes ownership, I'm not sure this is
        // intented (nor explicit) here
        m_graphicLayers[position] = std::make_unique<GraphicLayer>(layer);
    }
}

void Floor::setVisible(bool visible)
{
    m_visible = visible;
}

} // namespace Editor
