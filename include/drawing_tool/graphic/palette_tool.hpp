#pragma once

#include "drawing_tool/graphic/graphic_tool.hpp"

class QIcon;
class QGraphicsRectItem;
class QGraphicsPixmapItem;

namespace DrawingTool {

namespace Graphic {

class PaletteTool : public GraphicTool {
    Q_OBJECT
public:
    PaletteTool(QIcon&&, GraphicMap::VisibleGraphicLayer&);
    void paletteMousePressEvent(::QGraphicsSceneMouseEvent*);
    void paletteMouseMoveEvent(::QGraphicsSceneMouseEvent*);
    void paletteMouseReleaseEvent(::QGraphicsSceneMouseEvent*);
    void emitDrawingToolSelected() override;
    void setSelection(const QRect&, const QPixmap&);
    ::ChipsetGraphicsScene* chipsetGraphicsScene() const {
        return m_chipsetGraphicsScene;
    }
    void setChipsetGraphicsScene(::ChipsetGraphicsScene*);
signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTool::Graphic::PaletteTool*);
private:
    ::ChipsetGraphicsScene* m_chipsetGraphicsScene;
    QRect m_rectSelection;
    QPixmap m_selectionPixmap;
    ::QGraphicsRectItem* m_selectionRectItem;
    ::QGraphicsPixmapItem* m_selectionItem;
    bool m_isSelecting;
    QPoint m_selectionStart;
};

} // namespace Graphic
} // namespace DrawingTool
