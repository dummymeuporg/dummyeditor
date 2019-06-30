#include <QDebug>

#include "core/blocking_layer.hpp"
#include "core/graphic_layer.hpp"

#include "local/level.hpp"
#include "local/project.hpp"

#include "editor/blocking_layer.hpp"
#include "editor/graphic_layer.hpp"
#include "editor/level.hpp"
#include "editor/map.hpp"

namespace Editor {
Map::Map(const Dummy::Local::Project& project, const std::string& name)
    : Dummy::Local::Map(project, name) {}

Map::~Map() {}

void Map::load() {
    Dummy::Local::Map::load();
    /*
    for (const auto& level: m_levels) {
        m_editorLevels.push_back(std::make_unique<Level>(*this));
    }
    */
}

void Map::setChipset(const std::string& chipset) {
    m_chipset = chipset;
}
void Map::setMusic(const std::string& music) {
    m_music = music;
}

void Map::reset(std::uint16_t width, std::uint16_t height) {
    m_width = width;
    m_height = height;
}

void Map::save() {
    // Save the blocking layer, then the graphic info.
    _saveBlockingLayers();
    _saveGraphicLayers();
}

void
Map::_resizeGraphicLayer(
    Dummy::Core::GraphicLayer& graphicLayer,
    std::uint16_t width,
    std::uint16_t height)
{
    // XXX: fix this
    /*
    Dummy::Core::GraphicLayer newGraphicLayer(width * height);

    for (std::uint16_t y = 0; y < height; ++y) {
        for (std::uint16_t x = 0; x < width; ++x) {
            if (x < m_width && y < m_height) {
                newGraphicLayer[y * width + x] = graphicLayer[y * m_width + x];
            } else {
                newGraphicLayer[y * width + x] =
                    std::pair<std::int8_t, std::int8_t>(-1, -1);
            }
        }
    }
    graphicLayer = std::move(newGraphicLayer);
    */
}

void Map::_resizeBlockingLayer(std::uint16_t width, std::uint16_t height)
{
    Dummy::Core::BlockingLayer newBlockingLayer(width, height);

    // XXX: Fix this.
    /*
    for (std::uint16_t y = 0; y < height; ++y) {
        for (std::uint16_t x = 0; x < width; ++x) {
            if (x < m_width && y < m_height) {
                newBlockingLayer[y * width + x] =
                    m_blockingLayer[y * m_width + x];
            } else {
                newBlockingLayer[y * width + x] = 0;
            }
        }
    }
    m_blockingLayer = std::move(newBlockingLayer);
    */
}

void Map::resize(std::uint16_t width, std::uint16_t height) {
    _resizeBlockingLayer(width, height);
    m_width = width;
    m_height = height;

}

void Map::_saveBlockingLayers() {
    std::uint32_t magicNumber = BLK_MAGIC_WORD;
    std::uint16_t version = 2;
    std::string filename(m_name + ".blk");
    std::ofstream ofs(m_project.projectPath() / "maps" / filename,
                      std::ios::binary);

    // Write the magic number
    ofs.write(reinterpret_cast<const char*>(&magicNumber),
              sizeof(std::uint32_t));

    // Write the version number
    ofs.write(reinterpret_cast<const char*>(&version),
              sizeof(std::uint16_t));

    // Write the blocking layers
    for (auto& level: m_levels) {
        ofs.write(
            reinterpret_cast<const char*>(level.blockingLayer().data()),
            static_cast<std::streamsize>(
                level.blockingLayer().size() * sizeof(std::int8_t)
            )
        );
    }

    ofs.close();
}

void Map::_saveGraphicLayers() {
    std::uint32_t magicNumber = MAP_MAGIC_WORD;
    std::uint16_t version = 2; // XXX for now.
    std::string filename(m_name + ".map");
    std::ofstream ofs(m_project.projectPath() / "maps" / filename,
                      std::ios::binary);

    // write the magic number
    ofs.write(reinterpret_cast<const char*>(&magicNumber),
              sizeof(std::uint32_t));

    // write the version number
    ofs.write(reinterpret_cast<const char*>(&version),
              sizeof(std::uint16_t));

    // write the map's dimensions
    ofs.write(reinterpret_cast<const char*>(&m_width),
              sizeof(std::uint16_t));
    ofs.write(reinterpret_cast<const char*>(&m_height),
              sizeof(std::uint16_t));

    // write the levels count
    ofs.write(reinterpret_cast<char*>(&m_levelsCount), sizeof(std::uint8_t));

    // write the chipset
    _writeStdString(ofs, m_chipset);

    // write the music
    _writeStdString(ofs, m_music);

    // write the levels
    for(auto& level: m_levels) {
        writeLevel(ofs, level);
    }
}

void Map::_writeStdString(std::ofstream& ofs,
                                const std::string& str) {
    std::uint32_t size = static_cast<std::uint32_t>(str.size());
    ofs.write(reinterpret_cast<const char*>(&size),
              sizeof(std::uint32_t));
    if (size > 0) {
        ofs.write(str.c_str(), static_cast<std::streamsize>(str.size()));
    }
}

void
Map::writeLevel(
    std::ofstream& ofs,
    const Dummy::Local::Level& level
) const {
    // Write the layers count.
    std::uint8_t layersCount = level.graphicLayers().size();
    ofs.write(
        reinterpret_cast<char*>(&layersCount),
        sizeof(std::uint8_t)
    );

    for (const auto& [position, layer]: level.graphicLayers()) {
        ofs.write(
            reinterpret_cast<const char*>(&position),
            sizeof(std::int8_t)
        );
        ofs.write(
            reinterpret_cast<const char*>(layer->data()),
            static_cast<std::streamsize>(
                layer->size() * sizeof(std::pair<std::int8_t, std::int8_t>)
            )
        );
    }
}
} // namespace Editor
