#include "startingpoint.h"

Dummy::StartingPoint::StartingPoint()
{

}


Dummy::StartingPoint& Dummy::StartingPoint::setMapName(const char* mapName)
{
    m_mapName = mapName;
    return *this;
}

Dummy::StartingPoint& Dummy::StartingPoint::setX(std::uint16_t x)
{
    m_x = x;
    return *this;
}

Dummy::StartingPoint& Dummy::StartingPoint::setY(std::uint16_t y)
{
    m_y = y;
    return *this;
}
