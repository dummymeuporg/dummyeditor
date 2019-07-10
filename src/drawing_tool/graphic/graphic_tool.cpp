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
    QPen pen(Qt::black, 0.5);

    quint16 width = m_visibleGraphicLayer.layer().width();
    quint16 height = m_visibleGraphicLayer.layer().height();

    for (int i = 0; i <= width; ++i) {
        QGraphicsItem* item = m_mapGraphicsScene.addLine(
            i * 16, 0,
            i * 16,
            16 * height,
            pen
        );
        item->setZValue(88888);
    }

    for (int i = 0; i <= height; ++i) {
        QGraphicsItem* item = m_mapGraphicsScene.addLine(
            0,
            i * 16,
            16 * width,
            16 * i,
            pen
        );
        item->setZValue(88888);
    }
}

} // namespace Graphic
} // namespace DrawingTool
