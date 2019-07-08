#pragma once

#include <QRect>
#include "drawing_tool/drawing_tool.hpp"

namespace GraphicMap {
class VisibleGraphicLayer;
} // namespace GraphicMap

namespace DrawingTool {

class Visitor;

namespace Graphic {

class GraphicTool : public DrawingTool {
    Q_OBJECT
public:
    GraphicTool(QIcon&&, GraphicMap::VisibleGraphicLayer&);
    virtual void paletteMousePressEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void paletteMouseMoveEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void paletteMouseReleaseEvent(::QGraphicsSceneMouseEvent*) = 0;
    void emitDrawingToolSelected() override;
signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTool::Graphic::GraphicTool*);
public slots:
    void setChipsetSelection(QRect);
private:
    GraphicMap::VisibleGraphicLayer& m_visibleGraphicLayer;
    QRect m_chipsetSelection;
};


} // namespace Graphic

} // namespace DrawingTool
