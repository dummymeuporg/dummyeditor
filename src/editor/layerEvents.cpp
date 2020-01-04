#include "editor/layerEvents.hpp"

#include <dummy/core/blocking_layer.hpp>
#include <dummy/local/floor.hpp>

namespace Editor {

EventsLayer::EventsLayer(Dummy::Local::Floor& floor)
    : m_floor(floor)
{}

std::uint16_t EventsLayer::width() const
{
    return m_floor.width();
}

std::uint16_t EventsLayer::height() const
{
    return m_floor.height();
}

} // namespace Editor
