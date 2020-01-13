#ifndef EVENTSLAYER_H
#define EVENTSLAYER_H

#include <dummy/local/floor.hpp>

#include "editor/layer.hpp"

namespace Editor {

//////////////////////////////////////////////////////////////////////////////
//  EventsLayer class
//////////////////////////////////////////////////////////////////////////////

class EventsLayer : public Layer
{
public:
    EventsLayer(Dummy::Local::Floor&);
    Dummy::Local::Events& touchEvents() { return m_floor.touchEvents(); }
    std::uint16_t width() const;
    std::uint16_t height() const;
    Dummy::Local::Floor& floor() { return m_floor; }

private:
    Dummy::Local::Floor& m_floor;
};

} // namespace Editor

#endif // EVENTSLAYER_H
