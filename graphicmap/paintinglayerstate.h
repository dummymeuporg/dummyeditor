#pragma once

class QPoint;
class QRect;

namespace GraphicMap {

    class MapGraphicsScene;
    class SelectionDrawingClipboard;

    class PaintingLayerState
    {
    public:
        PaintingLayerState(MapGraphicsScene&);
        virtual ~PaintingLayerState();

        virtual void adjustLayers() = 0;
        virtual void onNewMap() = 0;
        virtual void sceneCleared() = 0;

        virtual void drawWithPen(const QPoint&) const = 0;
        virtual void drawWithRectangle(const QPoint&, const QRect&) const = 0;
        virtual void drawWithSelection(const QPoint&,
                                       const SelectionDrawingClipboard&)
            const = 0;

    protected:
        MapGraphicsScene& m_mapGraphicsScene;
    };

}
