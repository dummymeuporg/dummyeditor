#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <dummy/local/map.hpp>

#include "editor/layer.hpp"
#include "editor/level.hpp"

namespace Dummy {
namespace Core {
class GraphicLayer;
} // namespace Core
} // namespace Dummy

namespace Editor {
class Level;
using Levels = std::vector<std::unique_ptr<Level>>;

class Map : public Dummy::Local::Map {
public:
    Map(const Dummy::Local::Project&, const std::string&);
    virtual ~Map();

    void setChipset(const std::string&);
    void setMusic(const std::string&);
    void reset(std::uint16_t, std::uint16_t);

    void save();
    void resize(std::uint16_t, std::uint16_t);

    std::uint8_t levelsCount() const {
        return m_levelsCount;
    }

    Level& levelAt(std::uint8_t index) {
        return *m_editorLevels[index];
    }

    const Levels& levels() const {
        return m_editorLevels;
    }

    void addLevel(std::unique_ptr<Editor::Level>);

    GraphicLayer& graphicLayerAt(std::uint8_t level, std::int8_t position) {
        return m_editorLevels[level]->graphicLayerAt(position);
    }

    void load();

private:
    void saveBlockingLayers();
    void saveGraphicLayers();

    void resizeLevel(Editor::Level&, std::uint16_t, std::uint16_t);
    void resizeBlockingLayer(
        Editor::BlockingLayer&,
        std::uint16_t,
        std::uint16_t
    );
    void resizeGraphicLayer(
        Editor::GraphicLayer&,
        std::uint16_t,
        std::uint16_t
    );

    static void _writeStdString(std::ofstream&, const std::string&);
    void writeLevel(std::ofstream&, const Dummy::Local::Level&) const;
    Levels m_editorLevels;
};
} // namespace Editor
