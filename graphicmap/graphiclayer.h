#pragma once

#include <QtGlobal>

namespace GraphicMap {

    class MapGraphicsScene;

    class GraphicLayer
    {
    public:
        GraphicLayer(MapGraphicsScene&);
        virtual ~GraphicLayer();

        virtual void removeTile(quint16, quint16) = 0;

    protected:
        MapGraphicsScene& m_mapGraphicsScene;
    };
}
