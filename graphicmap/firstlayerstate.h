#pragma once

#include "graphicmap/paintinggraphiclayerstate.h"

namespace GraphicMap {
    class MapGraphicsScene;
    class FirstLayerState : public PaintingGraphicLayerState
    {
    public:
        FirstLayerState(MapGraphicsScene&);
        virtual ~FirstLayerState();
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    };
}
