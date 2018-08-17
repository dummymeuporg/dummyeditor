#pragma once

#include <string>
#include <cstdint>

namespace Dummy {
    class StartingPoint
    {
    public:
        StartingPoint();

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

        StartingPoint& setMapName(const char* mapName);
        StartingPoint& setX(std::uint16_t x);
        StartingPoint& setY(std::uint16_t y);

    private:
        std::string m_mapName;
        std::uint16_t m_x, m_y;
    };
}
