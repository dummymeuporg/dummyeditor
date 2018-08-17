#pragma once


#include "graphicmap/mapscenelayer.h"

class QGraphicsPixmapItem;
class QPoint;

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

        QGraphicsPixmapItem* startingPointItem() const
        {
            return m_startingPointItem;
        }

        void setStartingPointItem(const QPoint&);

    private:
        QGraphicsPixmapItem* m_startingPointItem;
    };
}
