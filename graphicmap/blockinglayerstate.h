#pragma once

#include "graphicmap/paintinglayerstate.h"

namespace GraphicMap {
    class BlockingLayerState : public PaintingLayerState
    {
    public:
        BlockingLayerState(MapGraphicsScene&);
        virtual ~BlockingLayerState() override;

        virtual void drawWithPen(const QPoint&) const override;
        virtual void drawWithRectangle(const QPoint&,
                                       const QRect&) const override;
        virtual void drawWithSelection(
            const QPoint&,
            const SelectionDrawingClipboard&) const override;

        virtual void adjustLayers() override;
        virtual void onNewMap() override;
        virtual void sceneCleared() override;
    };
}
