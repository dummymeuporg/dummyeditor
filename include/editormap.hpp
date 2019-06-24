#pragma once

#include <cstdint>
#include <string>

#include "core/graphic_map.hpp"

class EditorMap : public Dummy::Core::GraphicMap {
public:
    EditorMap(const Dummy::Core::Project&, const std::string&);
    virtual ~EditorMap();

    Dummy::Core::GraphicLayer& firstLayer() {
        return m_firstLayer;
    }

    Dummy::Core::GraphicLayer& secondLayer() {
        return m_secondLayer;
    }

    Dummy::Core::GraphicLayer& thirdLayer() {
        return m_thirdLayer;
    }

    Dummy::Core::GraphicLayer& fourthLayer() {
        return m_fourthLayer;
    }

    void setChipset(const std::string&);
    void setMusic(const std::string&);
    void reset(std::uint16_t, std::uint16_t);

    void save();
    void resize(std::uint16_t, std::uint16_t);
private:
    void _saveBlockingLayers();
    void _saveGraphicLayers();

    void _resizeBlockingLayer(std::uint16_t, std::uint16_t);
    void _resizeGraphicLayer(
        Dummy::Core::GraphicLayer&,
        std::uint16_t,
        std::uint16_t
    );

    static void _writeStdString(std::ofstream&, const std::string&);

};
