#pragma once

#include <QRect>

#include "graphicmap/drawingtool.h"

class QGraphicsRectItem;

namespace GraphicMap {
    class MapGraphicsScene;

    class SelectionDrawingTool : public DrawingTool
    {
    public:
        SelectionDrawingTool(MapGraphicsScene&);
        virtual ~SelectionDrawingTool() override;
        virtual void chipsetSelectionChanged(const QRect&) override;
        virtual void onMousePress(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseLeave() override;
        virtual void onMouseMove(QGraphicsSceneMouseEvent*) override;
        virtual void onMouseRelease(QGraphicsSceneMouseEvent*) override;
        virtual void onKeyPress(QKeyEvent*) override;
        virtual void onKeyRelease(QKeyEvent*) override;
    private:

        void _deleteSelection();

        QRect m_activeSelection;
        QPoint m_selectionStart;
        bool m_isSelecting;
        bool m_ctrlPressed;
        QGraphicsRectItem* m_selectionItem;
    };
}
