#pragma once

#include "graphicmap/drawingmapstate.h"

class QPoint;

namespace GraphicMap {

    class MapGraphicsScene;

    class PenDrawingMapState : public DrawingMapState
    {
    public:
        PenDrawingMapState(MapGraphicsScene&);
        virtual ~PenDrawingMapState();
        virtual void onMousePress(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) override;
        void _setTiles(const QPoint&);
    };
}
