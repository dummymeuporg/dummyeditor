#pragma once

#include "drawing_tool/graphic/graphic_tool.hpp"

class QIcon;

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
signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTool::Graphic::PaletteTool*);
public slots:
    void setChipsetSelection(QRect);
private:
    QRect m_chipsetSelection;
};

} // namespace Graphic
} // namespace DrawingTool
