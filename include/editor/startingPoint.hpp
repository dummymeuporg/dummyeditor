#ifndef STARTINGPOINT_H
#define STARTINGPOINT_H

#include <cstdint>
#include <string>

namespace Editor {
//////////////////////////////////////////////////////////////////////////////
//  StartingPoint class
//////////////////////////////////////////////////////////////////////////////

class StartingPoint
{
public:
    StartingPoint();
    StartingPoint(const char*, std::uint16_t, std::uint16_t, std::uint8_t);

    const char* mapName() const { return m_mapName.c_str(); }
    std::uint16_t x() const { return m_x; }
    std::uint16_t y() const { return m_y; }
    std::uint8_t floor() const { return m_floor; }

    // void setMapName(const char* mapName);
    void setX(std::uint16_t);
    void setY(std::uint16_t);
    void setFloor(std::uint8_t);

private:
    std::string m_mapName;
    std::uint16_t m_x;
    std::uint16_t m_y;
    std::uint8_t m_floor;
};
} // namespace Editor

#endif // STARTINGPOINT_H
