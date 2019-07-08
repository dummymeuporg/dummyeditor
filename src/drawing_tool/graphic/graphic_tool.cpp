#include <QDebug>

#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "drawing_tool/graphic/graphic_tool.hpp"
#include "drawing_tool/visitor.hpp"


namespace DrawingTool {
namespace Graphic {

GraphicTool::GraphicTool(
        QIcon&& icon,
        GraphicMap::VisibleGraphicLayer& visibleGraphicLayer)
    : DrawingTool(visibleGraphicLayer.mapGraphicsScene(), std::move(icon)),
      m_visibleGraphicLayer(visibleGraphicLayer)
{}

void GraphicTool::setChipsetSelection(QRect rect) {
    m_chipsetSelection = rect;
}

void GraphicTool::emitDrawingToolSelected() {
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

} // namespace Graphic
} // namespace DrawingTool
