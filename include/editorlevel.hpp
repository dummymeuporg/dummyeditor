#pragma once
#include <memory>
#include "core/map_level.hpp"

class EditorLayer;

using EditorLayers = std::map<std::int8_t, std::unique_ptr<EditorLayer>>;

class EditorLevel {
public:
    EditorLevel(const Dummy::Core::MapLevel&);
    EditorLayer& layerAt(std::int8_t position);
    void setLayer(std::int8_t, std::unique_ptr<EditorLayer>);
private:
    bool m_visible;
    const Dummy::Core::MapLevel& m_mapLevel;
    EditorLayers m_editorLayers;
};
