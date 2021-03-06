#ifndef FLOORLAYER_H
#define FLOORLAYER_H

#include <map>
#include <memory>

#include <dummy/local/floor.hpp>

#include "editor/layerBlocking.hpp"
#include "editor/layerEvents.hpp"
#include "editor/layerGraphic.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
using GraphicLayers = std::map<int8_t, std::unique_ptr<GraphicLayer>>;

//////////////////////////////////////////////////////////////////////////////
//  Floor class
//////////////////////////////////////////////////////////////////////////////

class Floor
{
public:
    explicit Floor(Dummy::Local::Floor&);

    GraphicLayer& graphicLayerAt(int8_t position); //< unimplemented...
    const GraphicLayers& graphicLayers() const { return m_graphicLayers; }
    bool visible() const { return m_visible; }
    void setVisible(bool);

    BlockingLayer& blockingLayer() { return m_blockingLayer; }
    EventsLayer& eventsLayer() { return m_eventsLayer; }
    Dummy::Local::Floor& localFloor() { return m_floor; }

private:
    Dummy::Local::Floor& m_floor;
    GraphicLayers m_graphicLayers;
    BlockingLayer m_blockingLayer;
    EventsLayer m_eventsLayer;
    bool m_visible = true;
};

} // namespace Editor

#endif // FLOORLAYER_H
