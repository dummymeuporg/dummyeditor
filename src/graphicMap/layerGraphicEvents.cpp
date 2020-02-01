#include "graphicMap/layerGraphicEvents.hpp"

#include "editor/layerEvents.hpp"
#include "graphicMap/graphicItem.hpp"
#include "utils/definitions.hpp"

namespace GraphicMap {

EventsGraphicLayer::EventsGraphicLayer(Editor::EventsLayer& eventsLayer, int zIndex)
    : GraphicMap::MapSceneLayer(zIndex)
    , m_eventsLayer(eventsLayer)
{
    const size_t nbCells = eventsLayer.width() * eventsLayer.height();
    const auto& touchEvents(eventsLayer.touchEvents());
    const auto& floor(eventsLayer.floor());
    indexedItems().resize(nbCells);

    for (size_t index = 0; index < nbCells; ++index) {
        if (touchEvents.find(index) != std::end(touchEvents)) {
            qreal posX((index % (floor.width())) * CELL_W);
            qreal posY((index / (floor.width())) * CELL_H);
            setTile(static_cast<quint16>(posX), static_cast<quint16>(posY), index);
        }
    }
}

void EventsGraphicLayer::setSelected()
{
    emit layerSelected(this);
}

void EventsGraphicLayer::setTile(quint16 x, quint16 y, int index)
{
    // TODO change this to correspond to other setTiles methods
    indexedItems()[index] = new GraphicItem(GraphicItem::eGraphicItemType::eEvent);
    indexedItems()[index]->setPos(QPointF(x - (x % CELL_W), y - (y % CELL_H)));
    graphicItems()->addToGroup(indexedItems()[index]);
}

} // namespace GraphicMap
