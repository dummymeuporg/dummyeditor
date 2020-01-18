#include "graphicMap/layerGraphic.hpp"

#include <QGraphicsItem>

#include "drawingTool/drawingTool.hpp"
#include "graphicMap/mapGraphicsScene.hpp"

namespace GraphicMap {
MapSceneLayer::MapSceneLayer(MapGraphicsScene& mapGraphicsScene, int zIndex)
    : m_mapGraphicsScene(mapGraphicsScene)
    , m_zIndex(zIndex)
{}


void MapSceneLayer::setVisibility(bool visible)
{
    for (auto* layerIt : layerItems()) {
        if (layerIt != nullptr) {
            layerIt->setVisible(visible);
        }
    }
}

void MapSceneLayer::setSelected()
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
