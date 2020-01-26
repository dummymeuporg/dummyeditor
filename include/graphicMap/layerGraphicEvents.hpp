#ifndef EVENTSGRAPHICLAYER_H
#define EVENTSGRAPHICLAYER_H

#include "graphicMap/layerGraphic.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class EventsLayer;
} // namespace Editor

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  EventsGraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class EventsGraphicLayer : public MapSceneLayer
{
    Q_OBJECT
public:
    explicit EventsGraphicLayer(Editor::EventsLayer&, int zIdx);

    std::shared_ptr<LayerClipboard::Clipboard> getClipboardRegion(const QRect& clip) override;

private:
    void setTile(quint16, quint16, int);

public slots:
    void setSelected() override;

signals:
    void layerSelected(GraphicMap::EventsGraphicLayer*);

private:
    Editor::EventsLayer& m_eventsLayer;
};

} // namespace GraphicMap

#endif // EVENTSGRAPHICLAYER_H
