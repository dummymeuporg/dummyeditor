#pragma once

#include "graphicmap/paintinglayerstate.h"

namespace GraphicMap {
    class PaintingBlockingLayerState : public PaintingLayerState
    {
    public:
        PaintingBlockingLayerState(MapGraphicsScene&);
        virtual ~PaintingBlockingLayerState() override;

        virtual void drawWithPen(const QPoint& point) const override;
        virtual void drawWithRectangle(const QPoint&,
                                       const QRect&) const override;
        virtual void drawWithSelection(
            const QPoint& point,
            const SelectionDrawingClipboard &clipboard) const override;
    };
}
