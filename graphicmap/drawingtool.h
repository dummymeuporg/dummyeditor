#pragma once

class QGraphicsSceneMouseEvent;

namespace GraphicMap {
    class MapGraphicsScene;

    class DrawingTool
    {
    public:
        DrawingTool(MapGraphicsScene&);
        virtual ~DrawingTool();
        virtual void onMousePress(QGraphicsSceneMouseEvent*) = 0;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) = 0;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) = 0;

    protected:
        MapGraphicsScene& m_mapGraphicScene;
        bool m_isDrawing;
    };
}
