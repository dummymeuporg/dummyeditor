#include "graphicMap/layerGraphicEvents.hpp"

#include "definitions.hpp"
#include "editor/layerEvents.hpp"
#include "graphicMap/graphicItem.hpp"
#include "graphicMap/graphicLayerVisitor.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace GraphicMap {

EventsGraphicLayer::EventsGraphicLayer(Editor::EventsLayer& eventsLayer,
                                       MapGraphicsScene& mapGraphicsScene,
                                       int zIndex)
    : GraphicMap::GraphicLayer(mapGraphicsScene, zIndex)
    , m_eventsLayer(eventsLayer)
{
    const auto& touchEvents(eventsLayer.touchEvents());
    const auto& floor(eventsLayer.floor());
    layerItems().resize(eventsLayer.width() * eventsLayer.height());

    /*

    for (auto it = m_layerItems.begin(); it != m_layerItems.end(); ++it,
    ++index)
    {
        *it = nullptr;
        if (touchEvents.find(index) != std::end(touchEvents))
        {
            qreal posX((index % (floor.width())) * 16);
            qreal posY((index / (floor.width())) * 16);
            draw(index, quint16(posX), quint16(posY));
        }
    }
     */
    for (size_t index = 0; index < layerItems().size(); ++index) {
        if (touchEvents.find(index) != std::end(touchEvents)) {
            qreal posX((index % (floor.width())) * CELL_W);
            qreal posY((index / (floor.width())) * CELL_H);
            draw(index, quint16(posX), quint16(posY));
        }
    }
}

void EventsGraphicLayer::draw(int index, quint16 x, quint16 y)
{
    layerItems()[index] = new GraphicItem(GraphicItem::eEventItem);
    layerItems()[index]->setZValue(zIndex());

    layerItems()[index]->setPos(QPointF(x - (x % CELL_W), y - (y % CELL_H)));

    mapGraphicsScene().addItem(layerItems()[index]);
}
/*
MapSceneLayer& EventsGraphicLayer::removeTile(quint16, quint16)
{
    return *this;
}
*/
std::vector<DrawingTools::DrawingTool*> EventsGraphicLayer::drawingTools()
{
    std::vector<DrawingTools::DrawingTool*> tools;
    return tools;
}

Editor::Layer& EventsGraphicLayer::editorLayer()
{
    return m_eventsLayer;
}

void EventsGraphicLayer::accept(GraphicLayerVisitor& visitor)
{
    visitor.visitGraphicLayer(*this);
}

std::shared_ptr<LayerClipboard::Clipboard>
EventsGraphicLayer::getClipboardRegion(const QRect& clip)
{
    // XXX: Todo later.
    return nullptr;
}


} // namespace GraphicMap
