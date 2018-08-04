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
        virtual void paintLayers() override;
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
    private:
        QGraphicsRectItem* m_firstDarkFilter;
    };
}
