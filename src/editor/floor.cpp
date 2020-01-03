#include "editor/floor.hpp"

#include <dummy/local/floor.hpp>

#include "editor/layerBlocking.hpp"
#include "editor/layerEvents.hpp"
#include "editor/layerGraphic.hpp"

namespace Editor {

Floor::Floor(Dummy::Local::Floor& floor)
    : m_floor(floor)
    , m_blockingLayer(nullptr)
    , m_eventsLayer(nullptr)
    , m_visible(true)
{
    m_blockingLayer = std::make_unique<BlockingLayer>(m_floor.blockingLayer());

    // TODO check this, this may become a problem of double deletion :
    // unique_ptr will want to delete if, but it's given as ref (floor)
    // so this is a wrongly implicit "give of ownership" of the referenced obj
    m_eventsLayer = std::make_unique<EventsLayer>(m_floor);

    for (auto& [position, layer]: m_floor.graphicLayers()) {
        // TODO same here, make_unique takes ownership, I'm not sure this is
        // intented (nor explicit) here
        m_graphicLayers[position] = std::make_unique<GraphicLayer>(layer);
    }
}

void Floor::setVisible(bool visible) {
    m_visible = visible;
}

} // namespace Editor
