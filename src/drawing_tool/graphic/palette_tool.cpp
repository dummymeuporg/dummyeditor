#include <QDebug>

#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "drawing_tool/graphic/palette_tool.hpp"
#include "drawing_tool/visitor.hpp"


namespace DrawingTool {
namespace Graphic {

PaletteTool::PaletteTool(
        QIcon&& icon,
        GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : GraphicTool(std::move(icon), visibleGraphicLayer)
{}

void PaletteTool::setChipsetSelection(QRect rect) {
    m_chipsetSelection = rect;
}

void PaletteTool::emitDrawingToolSelected() {
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void PaletteTool::paletteMousePressEvent(::QGraphicsSceneMouseEvent*) {

}

void PaletteTool::paletteMouseMoveEvent(::QGraphicsSceneMouseEvent*) {

}

void PaletteTool::paletteMouseReleaseEvent(::QGraphicsSceneMouseEvent*) {

}

} // namespace Graphic
} // namespace DrawingTool
