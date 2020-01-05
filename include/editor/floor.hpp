#ifndef FLOORLAYER_H
#define FLOORLAYER_H

#include <map>
#include <memory>

#include <dummy/local/floor.hpp>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class BlockingLayer;
class EventsLayer;
class GraphicLayer;
using GraphicLayers = std::map<int8_t, std::unique_ptr<GraphicLayer>>;

//////////////////////////////////////////////////////////////////////////////
//  Floor class
//////////////////////////////////////////////////////////////////////////////

class Floor
{
public:
    Floor(Dummy::Local::Floor&);

    GraphicLayer& graphicLayerAt(int8_t position); //< unimplemented...
    const GraphicLayers& graphicLayers() const { return m_graphicLayers; }
    bool visible() const { return m_visible; }
    void setVisible(bool);

    BlockingLayer& blockingLayer() { return *m_blockingLayer; }
    EventsLayer& eventsLayer() { return *m_eventsLayer; }
    GraphicLayers& graphicLayers() { return m_graphicLayers; }
    Dummy::Local::Floor& localFloor() { return m_floor; }

    /*
     * I comment this one, it is unused and may become problematic if
     * m_graphicLayers.at(position) returns nullptr

    GraphicLayer& graphicLayer(std::int8_t position) {
        return *(m_graphicLayers.at(position));
    }
    */

private:
    Dummy::Local::Floor& m_floor;
    std::unique_ptr<BlockingLayer> m_blockingLayer;
    std::unique_ptr<EventsLayer> m_eventsLayer;
    GraphicLayers m_graphicLayers;
    bool m_visible;
};

} // namespace Editor

#endif // FLOORLAYER_H
