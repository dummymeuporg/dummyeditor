#pragma once

#include <QGraphicsRectItem>

#include "graphicmap/paintinglayerstate.h"

namespace GraphicMap {
    class MapGraphicsScene;
    class SecondLayerState : public PaintingLayerState
    {
    public:
        SecondLayerState(MapGraphicsScene&);
        virtual ~SecondLayerState();
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    private:
        QGraphicsRectItem* m_firstDarkFilter;
    };
}
