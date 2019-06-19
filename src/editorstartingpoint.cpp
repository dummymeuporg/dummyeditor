#include <cstdint>
#include "editorstartingpoint.hpp"

EditorStartingPoint::EditorStartingPoint()
{

}

EditorStartingPoint::EditorStartingPoint(
    const char* mapName, std::uint16_t x, std::uint16_t y
) : m_mapName(mapName), m_x(x), m_y(y)
{}

EditorStartingPoint& EditorStartingPoint::setMapName(const char* mapName)
{
    m_mapName = mapName;
    return *this;
}

EditorStartingPoint& EditorStartingPoint::setX(std::uint16_t x)
{
    m_x = x;
    return *this;
}

EditorStartingPoint& EditorStartingPoint::setY(std::uint16_t y)
{
    m_y = y;
    return *this;
}
