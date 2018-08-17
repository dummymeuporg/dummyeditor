#pragma once

#include "graphicmap/paintinglayerstate.h"

namespace GraphicMap {
    class MapGraphicsScene;
    class SelectionDrawingClipboard;
    class NotPaintingState : public PaintingLayerState
    {
    public:
        NotPaintingState(MapGraphicsScene&);
        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;

        virtual void drawWithPen(const QPoint&) const override;
        virtual void drawWithRectangle(const QPoint&, const QRect&)
            const override;
        virtual void drawWithSelection(const QPoint&,
                                       const SelectionDrawingClipboard&)
            const override;
        virtual void drawCurrentSelection(const QPoint&, QGraphicsItem*)
            const override;
    };
}
