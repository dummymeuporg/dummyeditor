#pragma once

#include <QPixmap>
#include <QtGlobal>

#include "graphicmap/drawingtool.h"

class QGraphicsPixmapItem;
namespace GraphicMap {
    class MapGraphicsScene;

    class RectangleDrawingTool : public DrawingTool
    {
    public:
        RectangleDrawingTool(MapGraphicsScene&);
        virtual ~RectangleDrawingTool() override;

        virtual void chipsetSelectionChanged(const QRect&) override;
        virtual void onMousePress(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseLeave() override;
        virtual void onKeyPress(QKeyEvent*) override;
        virtual void onKeyRelease(QKeyEvent*) override;

    private:

        void _drawChipsetSelectionInRectangle();

        void _applyChipsetSelectionInRectangle();
        void _applySelectionToMap(quint16, quint16);


        // Rectangle Graphic Item to be drawn on the map edition.
        QGraphicsPixmapItem* m_selectionItem;

        // Whether the user has clicked on the scene or not.
        bool m_mouseCliked;

        // Pixmap referring to chipset selection
        QPixmap m_pixmapChipsetSelection;

        // Rectangle selected in the chipset.
        QRect m_rectChipsetSelection;

        // Rectangle being drawn by the user.
        QRect m_rectangle;
    };
}
