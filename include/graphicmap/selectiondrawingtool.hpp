#pragma once

#include <QRect>

#include <memory>

#include "graphicmap/drawingtool.hpp"

class QGraphicsRectItem;

namespace GraphicMap {
    class MapSceneLayer;
    class MapGraphicsScene;
    class SelectionDrawingClipboard;

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

        inline const QRect& activeSelection() const {
            return m_activeSelection;
        }

        inline const SelectionDrawingClipboard& clipboard() const {
            return *m_clipboard;
        }

    private:

        void _deleteSelection(MapSceneLayer*);
        void _applyClipboard();

        QRect m_activeSelection;
        QPoint m_selectionStart;
        bool m_isSelecting;
        bool m_ctrlPressed;
        QGraphicsRectItem* m_selectionItem;
        std::unique_ptr<SelectionDrawingClipboard> m_clipboard;
    };
}
