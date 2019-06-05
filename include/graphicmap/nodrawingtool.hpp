#pragma once

#include "graphicmap/drawingtool.hpp"

class QPoint;

class QGraphicsPixmapItem;
namespace GraphicMap {

    class MapGraphicsScene;

    class NoDrawingTool  : public DrawingTool
    {
    public:
        NoDrawingTool(MapGraphicsScene&);
        virtual ~NoDrawingTool();

        virtual void chipsetSelectionChanged(const QRect&) override;
        virtual void onMousePress(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseLeave() override;
        virtual void onKeyPress(QKeyEvent*) override;
        virtual void onKeyRelease(QKeyEvent*) override;
    };
}
