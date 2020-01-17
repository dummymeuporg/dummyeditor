#include "graphicMap/layerGraphicVisible.hpp"

#include <QGraphicsPixmapItem>

#include "definitions.hpp"
#include "editor/layerGraphic.hpp"
#include "editor/map.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

#include "layer_clipboard/visible.hpp"

namespace GraphicMap {

VisibleGraphicLayer::VisibleGraphicLayer(Editor::GraphicLayer& layer,
                                         MapGraphicsScene& mapGraphicsScene,
                                         const QPixmap& chipsetPixmap,
                                         int zIndex)
    : GraphicMap::GraphicLayer(mapGraphicsScene, zIndex)
    , m_graphicLayer(layer)
    , m_chipsetPixmap(chipsetPixmap)
{
    layerItems().resize(m_graphicLayer.width() * m_graphicLayer.height());

    size_t index = 0;
    for (const auto& cellCoord : m_graphicLayer.layer()) {
        layerItems()[index] = nullptr;
        qint16 x            = cellCoord.first;
        qint16 y            = cellCoord.second;
        if (x >= 0 && y >= 0) {
            layerItems()[index] = new QGraphicsPixmapItem(m_chipsetPixmap.copy(
                QRect(x * CELL_W, y * CELL_H, CELL_W, CELL_H)));

            qreal posX = (index % m_graphicLayer.width()) * CELL_W;
            qreal posY = (index / m_graphicLayer.width()) * CELL_H;

            layerItems()[index]->setPos(posX, posY);
            layerItems()[index]->setZValue(zIndex);
            layerItems()[index]->setOpacity(m_graphicLayer.visible() ? 1 : 0);
            mapGraphicsScene.addItem(layerItems()[index]);
            ++index;
        }
    }
}

VisibleGraphicLayer::~VisibleGraphicLayer() {}

/*
MapSceneLayer& VisibleGraphicLayer::removeTile(quint16 x, quint16 y)
{
    setTile(x, y, -1, -1);
    return *this;
}
*/
VisibleGraphicLayer& VisibleGraphicLayer::setTile(quint16 x, quint16 y,
                                                  qint16 chipsetX,
                                                  qint16 chipsetY)
{
    if (x < (m_graphicLayer.width() * CELL_W)
        && y < (m_graphicLayer.height() * CELL_H)) {
        unsigned long index =
            ((y / CELL_H) * m_graphicLayer.width()) + (x / CELL_W);

        if (nullptr != layerItems()[index]) {
            mapGraphicsScene().removeItem(layerItems()[index]);
            layerItems()[index] = nullptr;
        }

        if (chipsetX >= 0 && chipsetY >= 0) {
            layerItems()[index] = new QGraphicsPixmapItem(m_chipsetPixmap.copy(
                QRect(chipsetX, chipsetY, CELL_W, CELL_H)));
            layerItems()[index]->setPos(x, y);
            layerItems()[index]->setZValue(zIndex());
            mapGraphicsScene().addItem(layerItems()[index]);

            m_graphicLayer[index] = std::pair<std::int8_t, std::int8_t>(
                chipsetX / CELL_W, chipsetY / CELL_H);
        } else {
            m_graphicLayer[index] = std::pair<std::int8_t, std::int8_t>(-1, -1);
        }
    }

    return *this;
}

Editor::Layer& VisibleGraphicLayer::editorLayer()
{
    return m_graphicLayer;
}

std::vector<DrawingTools::DrawingTool*> VisibleGraphicLayer::drawingTools()
{
    // XXX: fill this.
    return {/*&m_pen, &m_rectangle, &m_eraser*/};
}

void VisibleGraphicLayer::accept(GraphicLayerVisitor& visitor)
{
    visitor.visitGraphicLayer(*this);
}

std::shared_ptr<LayerClipboard::Clipboard>
VisibleGraphicLayer::getClipboardRegion(const QRect& clip)
{
    const size_t x(clip.x() / CELL_W);
    const size_t y(clip.y() / CELL_H);
    const size_t width(clip.width() / CELL_W);
    const size_t height(clip.height() / CELL_H);

    std::vector<std::pair<std::int8_t, std::int8_t>> content;

    for (unsigned j = y; j <= (y + height); ++j) {
        for (size_t i = x; i <= (x + width); ++i) {
            size_t index((j * m_graphicLayer.width()) + i);
            content.push_back(m_graphicLayer.layer().at(index));
        }
    }

    return std::make_shared<LayerClipboard::Visible>(std::move(clip),
                                                     std::move(content));
}

} // namespace GraphicMap
