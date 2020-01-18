#ifndef EVENTSGRAPHICLAYER_H
#define EVENTSGRAPHICLAYER_H

#include "graphicMap/layerGraphic.hpp"
#include <QVector>

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
    EventsGraphicLayer(Editor::EventsLayer&, MapGraphicsScene&, int);

    // MapSceneLayer& removeTile(quint16, quint16) override;
    std::vector<DrawingTools::DrawingTool*> drawingTools() override;
    Editor::Layer& editorLayer() override;
    void accept(GraphicLayerVisitor&) override;

    std::shared_ptr<LayerClipboard::Clipboard>
    getClipboardRegion(const QRect& clip) override;

public slots:
    void setSelected() override;

signals:
    void layerSelected(GraphicMap::EventsGraphicLayer*);

private:
    void draw(int, quint16, quint16);

private:
    Editor::EventsLayer& m_eventsLayer;
    QVector<QGraphicsItem*> m_eventItems;
};

} // namespace GraphicMap

#endif // EVENTSGRAPHICLAYER_H
