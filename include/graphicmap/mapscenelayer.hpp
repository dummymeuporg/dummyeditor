#pragma once

#include <QtGlobal>

namespace GraphicMap {
    class MapGraphicsScene;
    class MapSceneLayer
    {
    public:
        MapSceneLayer(MapGraphicsScene&);
        virtual ~MapSceneLayer();

        virtual MapSceneLayer& setOpacity(qreal) = 0;
        virtual MapSceneLayer& removeTile(quint16, quint16) = 0;
    protected:
        MapGraphicsScene& m_mapGraphicsScene;
    };
}
