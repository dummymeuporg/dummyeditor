#pragma once
#include <map>
#include <memory>

#include <dummy/local/floor.hpp>

namespace Editor {
class BlockingLayer;
class GraphicLayer;
using GraphicLayers = std::map<std::int8_t, std::unique_ptr<GraphicLayer>>;

class Floor{
public:
    Floor(Dummy::Local::Floor&);
    GraphicLayer& graphicLayerAt(std::int8_t position);

    const GraphicLayers& graphicLayers() const {
        return m_graphicLayers;
    }
    bool visible() const {
        return m_visible;
    }
    void setVisible(bool);

    BlockingLayer& blockingLayer() {
        return *m_blockingLayer;
    }

    GraphicLayer& graphicLayer(std::int8_t position) {
        return *(m_graphicLayers.at(position));
    }

    GraphicLayers& graphicLayers() {
        return m_graphicLayers;
    }

    Dummy::Local::Floor& localFloor()  {
        return m_floor;
    }
private:
    Dummy::Local::Floor& m_floor;
    std::unique_ptr<BlockingLayer> m_blockingLayer;
    GraphicLayers m_graphicLayers;
    bool m_visible;
};

} // namespace Editor
