#pragma once
#include <map>
#include <memory>

namespace Dummy {
namespace Local {
class Level;
} // namespace Local
} // namespace Dummy

namespace Editor {
class BlockingLayer;
class GraphicLayer;

using GraphicLayers = std::map<std::int8_t, std::unique_ptr<GraphicLayer>>;

class Level {
public:
    Level(const Dummy::Local::Level&);
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
    const Dummy::Local::Level& m_level;
    std::unique_ptr<BlockingLayer> m_blockingLayer;
    GraphicLayers m_graphicLayers;
};

} // namespace Editor
