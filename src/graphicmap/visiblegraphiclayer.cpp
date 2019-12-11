#include <memory>
#include <iostream>

#include <QDebug>
#include <QGraphicsPixmapItem>

#include <dummy/core/graphic_layer.hpp>

#include "drawing_tool/graphic/pen.hpp"

#include "editor/map.hpp"
#include "editor/graphic_layer.hpp"

#include "graphicmap/mapgraphicsscene.hpp"
#include "graphicmap/visiblegraphiclayer.hpp"
#include "graphicmap/graphic_layer_visitor.hpp"

#include "layer_clipboard/visible.hpp"


namespace GraphicMap {

VisibleGraphicLayer::VisibleGraphicLayer(
    Editor::GraphicLayer& layer,
    MapGraphicsScene& mapGraphicsScene,
    const QPixmap& chipsetPixmap,
    int zIndex
) : GraphicMap::GraphicLayer(mapGraphicsScene, zIndex),
    m_graphicLayer(layer),
    m_chipsetPixmap(chipsetPixmap)
{
    m_layerItems.resize(m_graphicLayer.width() * m_graphicLayer.height());

    int index = 0;
    for (auto it = m_graphicLayer.layer().begin();
         it != m_graphicLayer.layer().end();
         ++it, ++index)
    {
        m_layerItems[index] = nullptr;
        qint16 x = std::get<0>(*it);
        qint16 y = std::get<1>(*it);
        if (x >= 0 && y >= 0)
        {
            m_layerItems[index] = new QGraphicsPixmapItem(
                m_chipsetPixmap.copy(QRect(x * 16, y * 16, 16, 16)));

            qreal posX = (index % m_graphicLayer.width()) * 16;
            qreal posY = (index / m_graphicLayer.width()) * 16;

            m_layerItems[index]->setPos(posX, posY);
            m_layerItems[index]->setZValue(m_zIndex);
            m_layerItems[index]->setOpacity(m_graphicLayer.visible() * 1);
            m_mapGraphicsScene.addItem(m_layerItems[index]);
        }
    }
}

VisibleGraphicLayer::~VisibleGraphicLayer()
{}


MapSceneLayer& VisibleGraphicLayer::removeTile(quint16 x, quint16 y)
{
    setTile(x, y, -1, -1);
    return *this;
}

VisibleGraphicLayer&
VisibleGraphicLayer::setTile(
    quint16 x,
    quint16 y,
    qint16 chipsetX,
    qint16 chipsetY
) {

    if (x < m_graphicLayer.width() * 16
        && y < m_graphicLayer.height() * 16)
    {
        unsigned long index = (y/16) * m_graphicLayer.width() + (x/16);

        if (nullptr != m_layerItems[index]) {
            m_mapGraphicsScene.removeItem(m_layerItems[index]);
            m_layerItems[index] = nullptr;
        }

        if (chipsetX >= 0 && chipsetY >= 0)
        {
            m_layerItems[index] = new
                QGraphicsPixmapItem(
                    m_chipsetPixmap.copy(QRect(chipsetX, chipsetY, 16, 16)));
            m_layerItems[index]->setPos(x, y);
            m_layerItems[index]->setZValue(m_zIndex);
            m_mapGraphicsScene.addItem(m_layerItems[index]);

            m_graphicLayer[index] = std::pair<std::int8_t, std::int8_t>(
                 chipsetX / 16, chipsetY / 16
            );
        }
        else
        {
            m_graphicLayer[index] =
                std::pair<std::int8_t, std::int8_t>(-1, -1);
        }
    }

    return *this;
}

Editor::Layer& VisibleGraphicLayer::editorLayer() {
    return m_graphicLayer;
}

std::vector<DrawingTool::DrawingTool*>
VisibleGraphicLayer::drawingTools() {
    // XXX: fill this.
    return {/*&m_pen, &m_rectangle, &m_eraser*/};
}

void VisibleGraphicLayer::accept(GraphicLayerVisitor& visitor) {
    visitor.visitGraphicLayer(*this);
}

std::shared_ptr<LayerClipboard::Clipboard>
VisibleGraphicLayer::getClipboardRegion(const QRect& clip) {
    unsigned x(clip.x() / 16);
    unsigned y(clip.y() / 16);
    unsigned width(clip.width() / 16);
    unsigned height(clip.width() / 16);

    std::vector<std::pair<std::int8_t, std::int8_t>> content;

    for (unsigned j = y; j < height; ++j) {
        for (unsigned i = x; i < width; ++i) {
            unsigned index(j * m_graphicLayer.width() + i);
            content.push_back(m_graphicLayer.layer().at(index));
        }
    }

    return std::make_shared<LayerClipboard::Visible>(
        std::move(clip), std::move(content)
    );
}

} // namespace GraphicMap
