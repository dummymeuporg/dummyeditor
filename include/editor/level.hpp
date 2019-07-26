#pragma once
#include <map>
#include <memory>

#include <dummy/local/level.hpp>

namespace Editor {
class BlockingLayer;
class GraphicLayer;
using GraphicLayers = std::map<std::int8_t, std::unique_ptr<GraphicLayer>>;

class Level{
public:
    Level(Dummy::Local::Level&);
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

    Dummy::Local::Level& localLevel()  {
        return m_level;
    }
private:
    Dummy::Local::Level& m_level;
    std::unique_ptr<BlockingLayer> m_blockingLayer;
    GraphicLayers m_graphicLayers;
    bool m_visible;
};

} // namespace Editor
