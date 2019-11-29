#include <iostream>

#include <QDebug>
#include <QGraphicsItem>

#include "drawing_tool/drawing_tool.hpp"
#include "editor/map.hpp"

#include "graphicmap/graphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

namespace GraphicMap {
GraphicLayer::GraphicLayer(MapGraphicsScene& mapGraphicsScene, int zIndex)
    : MapSceneLayer(mapGraphicsScene, zIndex)
{}


void GraphicLayer::setVisibility(bool visible) {
    for (auto it = m_layerItems.begin(); it != m_layerItems.end(); ++it)
    {
        if(*it != nullptr) {
            (*it)->setVisible(visible);
        }
    }
}

void GraphicLayer::setSelected() {
    emit layerSelected(this);

    // Bind the tool to this graphic layer
    auto drawingTool = m_mapGraphicsScene.drawingTool();
    if (nullptr != drawingTool) {
        accept(*drawingTool);
    }

    m_mapGraphicsScene.setCurrentGraphicLayer(this);
}

} // namespace GraphicMap
