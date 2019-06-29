#pragma once
#include <memory>
#include "core/map_level.hpp"

namespace Editor {
class BlockingLayer;
class GraphicLayer;

using GraphicLayers = std::map<std::int8_t, std::unique_ptr<GraphicLayer>>;

class Level {
public:
    Level(const Dummy::Core::MapLevel&);
    GraphicLayer& graphicLayerAt(std::int8_t position);
    void setGraphicLayer(std::int8_t, std::unique_ptr<GraphicLayer>);
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
private:
    bool m_visible;
    const Dummy::Core::MapLevel& m_mapLevel;
    std::unique_ptr<BlockingLayer> m_blockingLayer;
    GraphicLayers m_graphicLayers;
};

} // namespace Editor
