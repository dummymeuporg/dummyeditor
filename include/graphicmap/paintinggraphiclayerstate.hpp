#pragma once

#include "graphicmap/paintinglayerstate.hpp"

namespace GraphicMap
{
    class PaintingGraphicLayerState : public PaintingLayerState
    {
    public:
        PaintingGraphicLayerState(MapGraphicsScene&);
        virtual ~PaintingGraphicLayerState() override;

        virtual void drawWithPen(const QPoint& point) const override;
        virtual void drawWithRectangle(const QPoint&,
                                       const QRect&) const override;
        virtual void drawWithSelection(
            const QPoint& point,
            const SelectionDrawingClipboard &clipboard) const override;
        virtual void drawCurrentSelection(const QPoint&, QGraphicsItem*)
            const override;
    };
}
