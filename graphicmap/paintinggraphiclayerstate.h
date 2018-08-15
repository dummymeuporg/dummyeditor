#pragma once

#include "graphicmap/paintinglayerstate.h"

namespace GraphicMap
{
    class PaintingGraphicLayerState : public PaintingLayerState
    {
    public:
        PaintingGraphicLayerState(MapGraphicsScene&);
        virtual ~PaintingGraphicLayerState() override;

        virtual void drawWithPen(const QPoint& point) override;
        virtual void drawWithRectangle(const QPoint& point) override;
        virtual void drawWithSelection(const QPoint& point) override;
    };
}
