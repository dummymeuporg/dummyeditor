#pragma once

#include "graphicmap/paintinglayerstate.h"

namespace GraphicMap {
    class MapGraphicsScene;
    class FirstLayerState : public PaintingLayerState
    {
    public:
        FirstLayerState(MapGraphicsScene&);
        virtual ~FirstLayerState();
        virtual void paintLayers() override;
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
    };
}
