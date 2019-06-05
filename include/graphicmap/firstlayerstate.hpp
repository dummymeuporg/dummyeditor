#pragma once

#include "graphicmap/paintinggraphiclayerstate.hpp"

namespace GraphicMap {
    class MapGraphicsScene;
    class FirstLayerState : public PaintingGraphicLayerState
    {
    public:
        FirstLayerState(MapGraphicsScene&);
        virtual ~FirstLayerState() override;
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    };
}
