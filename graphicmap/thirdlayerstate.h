#pragma once

#include "graphicmap/paintinggraphiclayerstate.h"

class QGraphicsRectItem;

namespace GraphicMap {
    class MapGraphicsScene;
    class ThirdLayerState : public PaintingGraphicLayerState
    {
    public:
        ThirdLayerState(MapGraphicsScene&);
        virtual ~ThirdLayerState() override;
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    private:
        QGraphicsRectItem* m_firstDarkFilter;
        QGraphicsRectItem* m_secondDarkFilter;
    };
}
