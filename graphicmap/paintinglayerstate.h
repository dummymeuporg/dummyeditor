#pragma once

namespace GraphicMap {

    class MapGraphicsScene;

    class PaintingLayerState
    {
    public:
        PaintingLayerState(MapGraphicsScene&);
        virtual ~PaintingLayerState();
        virtual void paintLayers() = 0;
        virtual void adjustLayers() = 0;
        virtual void onNewMap();

    protected:
        MapGraphicsScene& m_mapGraphicsScene;
    };

}
