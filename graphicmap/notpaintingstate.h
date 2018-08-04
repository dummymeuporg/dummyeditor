#pragma once

#include "graphicmap/paintinglayerstate.h"

namespace GraphicMap {
    class MapGraphicsScene;
    class NotPaintingState : public PaintingLayerState
    {
    public:
        NotPaintingState(MapGraphicsScene&);
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    };
}
