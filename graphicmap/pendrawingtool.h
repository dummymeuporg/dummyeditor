#pragma once

#include "graphicmap/drawingtool.h"

class QPoint;

namespace GraphicMap {

    class MapGraphicsScene;

    class PenDrawingTool : public DrawingTool
    {
    public:
        PenDrawingTool(MapGraphicsScene&);
        virtual ~PenDrawingTool();
        virtual void onMousePress(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) override;
        void _setTiles(const QPoint&);
    };
}
