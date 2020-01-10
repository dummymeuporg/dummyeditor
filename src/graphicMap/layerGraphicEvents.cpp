#include "graphicMap/layerGraphicEvents.hpp"

#include "editor/layerEvents.hpp"
#include "graphicMap/eventItemSquare.hpp"
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
    m_layerItems.resize(eventsLayer.width() * eventsLayer.height());

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
    for (size_t index = 0; index < m_layerItems.size(); ++index) {
        if (touchEvents.find(index) != std::end(touchEvents)) {
            qreal posX((index % (floor.width())) * 16);
            qreal posY((index / (floor.width())) * 16);
            draw(index, quint16(posX), quint16(posY));
        }
    }
}

void EventsGraphicLayer::draw(int index, quint16 x, quint16 y)
{
    m_layerItems[index] = new EventSquareItem();
    m_layerItems[index]->setZValue(m_zIndex);

    m_layerItems[index]->setPos(QPointF(x - (x % 16), y - (y % 16)));

    m_mapGraphicsScene.addItem(m_layerItems[index]);
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
