#pragma once

#include <QPixmap>

#include "graphicmap/drawingtool.hpp"

class QPoint;

class QGraphicsPixmapItem;
namespace GraphicMap {


    class MapGraphicsScene;

    class PenDrawingTool : public DrawingTool
    {
    public:
        PenDrawingTool(MapGraphicsScene&);
        virtual ~PenDrawingTool();

        virtual void chipsetSelectionChanged(const QRect&) override;
        virtual void onMousePress(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseLeave() override;
        virtual void onKeyPress(QKeyEvent*) override;
        virtual void onKeyRelease(QKeyEvent*) override;

    private:

        void _drawCurrentSelection(const QPoint& point);
        void _setTiles(const QPoint&);

        QGraphicsPixmapItem* m_selectionItem;
    };
}
