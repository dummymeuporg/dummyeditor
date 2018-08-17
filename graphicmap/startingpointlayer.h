#pragma once


#include "graphicmap/mapscenelayer.h"

class QGraphicsPixmapItem;

namespace GraphicMap
{
    class MapGraphicsScene;
    class StartingPointLayer : public MapSceneLayer
    {
    public:
        StartingPointLayer(MapGraphicsScene&);
        virtual ~StartingPointLayer() override;

        virtual MapSceneLayer& setOpacity(qreal) override;
        virtual MapSceneLayer& removeTile(quint16, quint16) override;

    private:
        QGraphicsPixmapItem* m_startingPointItem;
    };
}
