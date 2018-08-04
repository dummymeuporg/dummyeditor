#pragma once

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class MapGraphicsScene;

    class DrawingMapState
    {
    public:
        DrawingMapState(MapGraphicsScene&);
        virtual ~DrawingMapState();
        virtual void onMousePress(QGraphicsSceneMouseEvent*) = 0;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) = 0;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) = 0;

    protected:
        MapGraphicsScene& m_mapGraphicScene;
        bool m_isDrawing;
    };
}
