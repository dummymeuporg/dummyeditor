#pragma once

#include <string>
#include <cstdint>


class EditorStartingPoint
{
public:
    EditorStartingPoint();
    EditorStartingPoint(const char*, std::uint16_t, std::uint16_t);

    inline const char* mapName() const
    {
        return m_mapName.c_str();
    }

    std::uint16_t x() const
    {
        return m_x;
    }

    std::uint16_t y() const
    {
        return m_y;
    }

    EditorStartingPoint& setMapName(const char* mapName);
    EditorStartingPoint& setX(std::uint16_t x);
    EditorStartingPoint& setY(std::uint16_t y);

private:
    std::string m_mapName;
    std::uint16_t m_x, m_y;
};

