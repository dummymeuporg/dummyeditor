#include "editormap.hpp"

EditorMap::EditorMap(const Dummy::Core::Project& project,
                     const std::string& name)
    : Dummy::Core::GraphicMap(project, name) {}

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
    m_firstLayer.resize(m_width * m_height * 2 * sizeof(std::int8_t), reset);
    m_secondLayer.resize(m_width * m_height * 2 * sizeof(std::int8_t), reset);
    m_thirdLayer.resize(m_width * m_height * 2 * sizeof(std::int8_t), reset);
    m_fourthLayer.resize(m_width * m_height * 2 * sizeof(std::int8_t), reset);
}
