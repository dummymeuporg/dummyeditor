#include "editor/starting_point.hpp"

namespace Editor {
StartingPoint::StartingPoint()
{}

StartingPoint::StartingPoint(
        const char* mapName,
        std::uint16_t x,
        std::uint16_t y,
        std::uint8_t floor)
    : m_mapName(mapName)
    , m_x(x)
    , m_y(y)
    , m_floor(floor)
{}
/*
void StartingPoint::setMapName(const char* mapName)
{
    m_mapName = mapName;
    return *this;
}*/

void  StartingPoint::setX(std::uint16_t x)
{
    m_x = x;
}

void StartingPoint::setY(std::uint16_t y)
{
    m_y = y;
}

void StartingPoint::setFloor(std::uint8_t floor) {
    m_floor = floor;
}
} // namespace Editor
