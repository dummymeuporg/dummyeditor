#pragma once

#include <QPixmap>

#include "graphicmap/drawingtool.h"

class QGraphicsPixmapItem;
namespace GraphicMap {
    class MapGraphicsScene;

    class RectangleDrawingTool : public DrawingTool
    {
    public:
        RectangleDrawingTool(MapGraphicsScene&);
        virtual ~RectangleDrawingTool();

        virtual void chipsetSelectionChanged(const QRect&) override;
        virtual void onMousePress(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseLeave() override;

    private:

        void _drawChipsetSelectionInRectangle();

        QGraphicsPixmapItem* m_selectionItem;
        bool m_mouseCliked;
        QPixmap m_pixmapChipsetSelection;
        QRect m_rectChipsetSelection;
        QRect m_rectangle;
    };
}
