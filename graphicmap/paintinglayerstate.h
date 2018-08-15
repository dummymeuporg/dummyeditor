#pragma once

class QPoint;

namespace GraphicMap {

    class MapGraphicsScene;

    class PaintingLayerState
    {
    public:
        PaintingLayerState(MapGraphicsScene&);
        virtual ~PaintingLayerState();

        virtual void adjustLayers() = 0;
        virtual void onNewMap() = 0;
        virtual void sceneCleared() = 0;

        virtual void drawWithPen(const QPoint&) = 0;
        virtual void drawWithRectangle(const QPoint&) = 0;
        virtual void drawWithSelection(const QPoint&) = 0;

    protected:
        MapGraphicsScene& m_mapGraphicsScene;
    };

}
