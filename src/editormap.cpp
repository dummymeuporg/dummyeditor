#include <QDebug>
#include "core/map_level.hpp"
#include "core/project.hpp"

#include "editormap.hpp"

EditorMap::EditorMap(const Dummy::Core::Project& project,
                     const std::string& name)
    : Dummy::Core::GraphicMap(project, name) {
    for (const auto& level: m_mapLevels) {
        m_editorLevels.push_back(EditorLevel(level));
    }
}

EditorMap::~EditorMap() {}

void EditorMap::setChipset(const std::string& chipset) {
    m_chipset = chipset;
}
void EditorMap::setMusic(const std::string& music) {
    m_music = music;
}

void EditorMap::reset(std::uint16_t width, std::uint16_t height) {
    m_width = width;
    m_height = height;

    // The blocking layers is twice bigger the graphic layers.
    m_blockingLayer.resize(m_width * 2 * m_height * 2 * sizeof(std::uint8_t));

    std::pair<std::int8_t, std::int8_t> reset(-1, -1);
    m_firstLayer.resize(m_width * m_height, reset);
    m_secondLayer.resize(m_width * m_height, reset);
    m_thirdLayer.resize(m_width * m_height, reset);
    m_fourthLayer.resize(m_width * m_height, reset);
}

void EditorMap::save() {
    // Save the blocking layer, then the graphic info.
    _saveBlockingLayers();
    _saveGraphicLayers();
}

void
EditorMap::_resizeGraphicLayer(
    Dummy::Core::GraphicLayer& graphicLayer,
    std::uint16_t width,
    std::uint16_t height)
{
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
}

void EditorMap::_resizeBlockingLayer(std::uint16_t width, std::uint16_t height)
{
    Dummy::Core::BlockingLayer newBlockingLayer(width * height);

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
}

void EditorMap::resize(std::uint16_t width, std::uint16_t height) {
    _resizeBlockingLayer(width, height);
    _resizeGraphicLayer(m_firstLayer, width, height);
    _resizeGraphicLayer(m_secondLayer, width, height);
    _resizeGraphicLayer(m_thirdLayer, width, height);
    _resizeGraphicLayer(m_fourthLayer, width, height);
    m_width = width;
    m_height = height;

}

void EditorMap::_saveBlockingLayers() {
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
    for (const auto& blockingLayer: m_blockingLevels) {
        ofs.write(
            reinterpret_cast<const char*>(blockingLayer.data()),
            static_cast<std::streamsize>(
                blockingLayer.size() * sizeof(std::int8_t)
            )
        );
    }

    ofs.close();
}

void EditorMap::_saveGraphicLayers() {
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

    // Write the levels count
    //ofs.write(reinterpret_cast<char*>(&levelsCount), sizeof(levelsCount));

    // write the layers
    for(const auto& mapLevel: m_mapLevels) {
        _writeLevel(ofs, mapLevel);
    }
    /*
    ofs.write(
        reinterpret_cast<const char*>(m_firstLayer.data()),
        static_cast<std::streamsize>(
            m_firstLayer.size() * sizeof(std::pair<std::int8_t, std::int8_t>)
        )
    );
    ofs.write(
        reinterpret_cast<const char*>(m_secondLayer.data()),
        static_cast<std::streamsize>(
            m_secondLayer.size() * sizeof(std::pair<std::int8_t, std::int8_t>)
        )
    );
    ofs.write(
        reinterpret_cast<const char*>(m_thirdLayer.data()),
        static_cast<std::streamsize>(
            m_thirdLayer.size() * sizeof(std::pair<std::int8_t, std::int8_t>)
        )
    );
    ofs.write(
        reinterpret_cast<const char*>(m_fourthLayer.data()),
        static_cast<std::streamsize>(
            m_fourthLayer.size() * sizeof(std::pair<std::int8_t, std::int8_t>)
        )
    );
    */
}

void EditorMap::_writeStdString(std::ofstream& ofs,
                                const std::string& str) {
    std::uint32_t size = static_cast<std::uint32_t>(str.size());
    ofs.write(reinterpret_cast<const char*>(&size),
              sizeof(std::uint32_t));
    if (size > 0) {
        ofs.write(str.c_str(), static_cast<std::streamsize>(str.size()));
    }
}

void
EditorMap::_writeLevel(
    std::ofstream& ofs,
    const Dummy::Core::MapLevel& levelMap
) {
    // Write the layers count.
    std::uint8_t layersCount = levelMap.layers().size();
    ofs.write(
        reinterpret_cast<char*>(&layersCount),
        sizeof(std::uint8_t)
    );

    for (const auto& [position, layer]: levelMap.layers()) {
        ofs.write(
            reinterpret_cast<const char*>(&position),
            sizeof(std::int8_t)
        );
        ofs.write(
            reinterpret_cast<const char*>(layer.data()),
            static_cast<std::streamsize>(
                layer.size() * sizeof(std::pair<std::int8_t, std::int8_t>)
            )
        );
    }
}
