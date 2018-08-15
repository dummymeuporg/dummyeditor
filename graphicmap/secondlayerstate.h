#pragma once

#include <QGraphicsRectItem>

#include "graphicmap/paintinggraphiclayerstate.h"

namespace GraphicMap {
    class MapGraphicsScene;
    class SecondLayerState : public PaintingGraphicLayerState
    {
    public:
        SecondLayerState(MapGraphicsScene&);
        virtual ~SecondLayerState() override;
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    private:
        QGraphicsRectItem* m_firstDarkFilter;
    };
}
