#pragma once
#include <memory>
#include "core/map_level.hpp"

namespace Editor {
class Layer;

using Layers = std::map<std::int8_t, std::unique_ptr<Layer>>;

class Level {
public:
    Level(const Dummy::Core::MapLevel&);
    Layer& layerAt(std::int8_t position);
    void setLayer(std::int8_t, std::unique_ptr<Layer>);
    const Layers& editorLayers() const {
        return m_editorLayers;
    }
    bool visible() const {
        return m_visible;
    }
    void setVisible(bool);
private:
    bool m_visible;
    const Dummy::Core::MapLevel& m_mapLevel;
    Layers m_editorLayers;
};

} // namespace Editor
