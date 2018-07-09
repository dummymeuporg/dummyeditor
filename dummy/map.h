#ifndef _DUMMY_MAP_H
#define _DUMMY_MAP_H

#include <QString>
#include <QtGlobal>

namespace Dummy {
    class Map
    {
    public:
        Map();
    private:
        QString m_name;
        quint16 m_width, m_height; // Map dimension
    };
}

#endif // _DUMMY_MAP_H
