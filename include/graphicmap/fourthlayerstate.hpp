#pragma once

#include "graphicmap/paintinggraphiclayerstate.hpp"

class QGraphicsRectItem;

namespace GraphicMap
{
    class FourthLayerState : public PaintingGraphicLayerState
    {
    public:
        FourthLayerState(MapGraphicsScene&);
        virtual ~FourthLayerState() override;
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    private:
        QGraphicsRectItem* m_firstDarkFilter;
        QGraphicsRectItem* m_secondDarkFilter;
        QGraphicsRectItem* m_thirdDarkFilter;
    };
}
