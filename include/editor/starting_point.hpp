#pragma once

#include <string>
#include <cstdint>


namespace Editor {
class StartingPoint
{
public:
    StartingPoint();
    StartingPoint(
        const char*,
        std::uint16_t,
        std::uint16_t,
        std::uint8_t
    );

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

    std::uint8_t floor() const {
        return m_floor;
    }

    StartingPoint& setMapName(const char* mapName);
    StartingPoint& setX(std::uint16_t);
    StartingPoint& setY(std::uint16_t);
    StartingPoint& setFloor(std::uint8_t);

private:
    std::string m_mapName;
    std::uint16_t m_x, m_y;
    std::uint8_t m_floor;
};
} // namespace Editor
