#pragma once

class QGraphicsSceneMouseEvent;
class QRect;
class QKeyEvent;

namespace GraphicMap {
    class MapGraphicsScene;

    class DrawingTool
    {
    public:
        DrawingTool(MapGraphicsScene&);
        virtual ~DrawingTool();
        virtual void chipsetSelectionChanged(const QRect&) = 0;
        virtual void onMousePress(QGraphicsSceneMouseEvent*) = 0;
        virtual void onMouseLeave() = 0;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) = 0;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) = 0;
        virtual void onKeyPress(QKeyEvent*) = 0;
        virtual void onKeyRelease(QKeyEvent*) = 0;

        inline const MapGraphicsScene& mapGraphicsScene() const {
            return m_mapGraphicScene;
        }

    protected:
        MapGraphicsScene& m_mapGraphicScene;
        bool m_isDrawing;
    };
}
