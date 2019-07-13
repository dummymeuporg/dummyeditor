#include <QDebug>
#include <QGraphicsItem>

#include "editor/graphic_layer.hpp"
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

void GraphicTool::emitDrawingToolSelected() {
    DrawingTool::emitDrawingToolSelected();
    qDebug() << "Emit drawing tool selected.";
    emit drawingToolSelected(this);
}

void GraphicTool::drawGrid() {
    m_mapGraphicsScene.drawGrid(
        m_visibleGraphicLayer.layer().width(),
        m_visibleGraphicLayer.layer().height(),
        16
    );
}

} // namespace Graphic
} // namespace DrawingTool
