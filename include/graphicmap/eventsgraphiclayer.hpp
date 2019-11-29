#pragma once

#include "graphicmap/graphiclayer.hpp"

namespace Editor {
class EventsLayer;
} // namespace Editor

namespace GraphicMap {

class EventsGraphicLayer : public GraphicLayer {
public:
    EventsGraphicLayer(Editor::EventsLayer&, MapGraphicsScene&, int);
    MapSceneLayer& removeTile(quint16, quint16) override;
    std::vector<DrawingTool::DrawingTool*> drawingTools() override;
    Editor::Layer& editorLayer() override;
    void accept(GraphicLayerVisitor&) override;
private:
    void draw(int, quint16, quint16);
    Editor::EventsLayer& m_eventsLayer;
    QVector<QGraphicsItem*> m_eventItems;
};

} // namespace GraphicMap
