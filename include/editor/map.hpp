#ifndef EDITORMAP_H
#define EDITORMAP_H

#include <cstdint>
#include <memory>
#include <string>

#include <dummy/local/map.hpp>

#include "editor/layer.hpp"
#include "editor/floor.hpp"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

namespace Dummy {
namespace Core {
class GraphicLayer;
} // namespace Core
} // namespace Dummy

namespace Editor {
class Floor;
using Floors = std::vector<std::unique_ptr<Floor>>;

//////////////////////////////////////////////////////////////////////////////
//  Map class
//////////////////////////////////////////////////////////////////////////////

class Map : public Dummy::Local::Map {
public:
    Map(const Dummy::Local::Project&, const std::string&);
    virtual ~Map();

    void setChipset(const std::string&);
    void setMusic(const std::string&);
    void reset(std::uint16_t, std::uint16_t);

    void save();
    void resize(std::uint16_t, std::uint16_t);

    std::uint8_t floorsCount() const { return m_floorsCount; }
    Floor& floorAt(std::uint8_t index) { return *m_editorFloors[index]; }
    const Floors& floors() const { return m_editorFloors; }

    void addFloor(std::unique_ptr<Editor::Floor>);

    GraphicLayer& graphicLayerAt(std::uint8_t floor, std::int8_t position) {
        return m_editorFloors[floor]->graphicLayerAt(position);
    }

    void load();

private:
    void saveBlockingLayers();
    void saveGraphicLayers();
    void saveEventsFile();

    void resizeFloor(Editor::Floor&, std::uint16_t, std::uint16_t);
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
    void writeFloor(std::ofstream&, const Dummy::Local::Floor&) const;
    Floors m_editorFloors;
};
} // namespace Editor

#endif // EDITORMAP_H
