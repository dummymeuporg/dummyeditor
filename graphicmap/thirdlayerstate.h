#pragma once

#include "graphicmap/paintinglayerstate.h"

class QGraphicsRectItem;

namespace GraphicMap {
    class MapGraphicsScene;
    class ThirdLayerState : public PaintingLayerState
    {
    public:
        ThirdLayerState(MapGraphicsScene&);
        virtual ~ThirdLayerState();
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    private:
        QGraphicsRectItem* m_firstDarkFilter;
        QGraphicsRectItem* m_secondDarkFilter;
    };
}
