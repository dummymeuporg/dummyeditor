#pragma once

#include <QPair>

class QPoint;
class QRect;
class QGraphicsItem;

namespace GraphicMap {

    class MapGraphicsScene;
    class SelectionDrawingClipboard;

    class PaintingLayerState
    {
    public:
        PaintingLayerState(MapGraphicsScene&, const QPair<int, int>&);
        virtual ~PaintingLayerState();

        virtual void adjustLayers() = 0;
        virtual void onNewMap() = 0;
        virtual void sceneCleared() = 0;

        void drawGrid();

        virtual void drawWithPen(const QPoint&) const = 0;
        virtual void drawWithRectangle(const QPoint&, const QRect&) const = 0;
        virtual void drawWithSelection(const QPoint&,
                                       const SelectionDrawingClipboard&)
            const = 0;
        virtual void drawCurrentSelection(const QPoint&, QGraphicsItem*)
            const = 0;

    protected:
        MapGraphicsScene& m_mapGraphicsScene;
        QPair<int, int> m_gridSize;
    };

}
