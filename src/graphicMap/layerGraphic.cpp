#include "graphicMap/layerGraphic.hpp"

#include <QGraphicsItem>

#include "drawingTool/drawingTool.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace GraphicMap {
GraphicLayer::GraphicLayer(MapGraphicsScene& mapGraphicsScene, int zIndex)
    : MapSceneLayer(mapGraphicsScene, zIndex)
{}


void GraphicLayer::setVisibility(bool visible)
{
    for (auto* layerIt : layerItems()) {
        if (layerIt != nullptr) {
            layerIt->setVisible(visible);
        }
    }
}

void GraphicLayer::setSelected()
{
    emit layerSelected(this);

    // Bind the tool to this graphic layer
    auto* drawingTool = mapGraphicsScene().drawingTool();
    if (nullptr != drawingTool) {
        accept(*drawingTool);
    }

    mapGraphicsScene().setCurrentGraphicLayer(this);
}

} // namespace GraphicMap
