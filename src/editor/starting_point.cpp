#include <cstdint>
#include "editor/starting_point.hpp"

namespace Editor {
StartingPoint::StartingPoint()
{

}

StartingPoint::StartingPoint(
    const char* mapName, std::uint16_t x, std::uint16_t y
) : m_mapName(mapName), m_x(x), m_y(y)
{}

StartingPoint& StartingPoint::setMapName(const char* mapName)
{
    m_mapName = mapName;
    return *this;
}

StartingPoint& StartingPoint::setX(std::uint16_t x)
{
    m_x = x;
    return *this;
}

StartingPoint& StartingPoint::setY(std::uint16_t y)
{
    m_y = y;
    return *this;
}
} // namespace Editor
