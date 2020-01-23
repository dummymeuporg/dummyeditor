#include "graphicMap/mapGraphicsScene.hpp"

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "editor/map.hpp"
#include "editor/project.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/layerGraphicEvents.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "utils/definitions.hpp"
#include "utils/Logger.hpp"
#include "utils/mapDocument.hpp"

using std::unique_ptr;

namespace GraphicMap {

MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
    installEventFilter(this);
}

MapGraphicsScene::~MapGraphicsScene() {}
const std::shared_ptr<MapDocument> MapGraphicsScene::mapDocument() const
{
    return m_mapDocument;
}

const vec_uniq<VisibleGraphicLayer>& MapGraphicsScene::graphicLayers() const
{
    return m_visibleLayers;
}
const vec_uniq<BlockingGraphicLayer>& MapGraphicsScene::blockingLayers() const
{
    return m_blockingLayers;
}
const vec_uniq<EventsGraphicLayer>& MapGraphicsScene::eventLayers() const
{
    return m_eventLayers;
}

void MapGraphicsScene::setMapDocument(
    const std::shared_ptr<MapDocument>& mapDocument)
{
    if (m_map != nullptr) {
        QRect invalidateRegion(0, 0, m_map->width() * CELL_W,
                               m_map->height() * CELL_H);
        qDebug() << "INVALIDATE " << invalidateRegion;
        invalidate(invalidateRegion);
    }
    // Clear the scene
    clearGrid();
    clear();

    m_mapDocument = mapDocument;
    m_map         = m_mapDocument->m_map;

    const Editor::Project& project = m_mapDocument->m_project;
    m_mapChipset                   = QPixmap(QString::fromStdString(
        (project.coreProject().projectPath() / "chipsets" / m_map->chipset())
            .string()));

    m_currentGraphicLayer = nullptr;

    m_visibleLayers.clear();
    m_blockingLayers.clear();
    m_eventLayers.clear();

    int zindex = 0;
    for (const auto& floor : m_map->floors()) {
        for (const auto& [position, layer] : floor->graphicLayers()) {
            qDebug() << "Position: " << position;

            unique_ptr<VisibleGraphicLayer> pGraphicLayer(
                new VisibleGraphicLayer(*layer, *this, m_mapChipset, ++zindex));


            QObject::connect(&pGraphicLayer->editorLayer(),
                             SIGNAL(visibilityChanged(bool)),
                             pGraphicLayer.get(), SLOT(setVisibility(bool)));

            QObject::connect(&pGraphicLayer->editorLayer(),
                             SIGNAL(setSelected()), pGraphicLayer.get(),
                             SLOT(setSelected()));

            m_visibleLayers.push_back(std::move(pGraphicLayer));
        }

        // Add blocking layer
        {
            unique_ptr<BlockingGraphicLayer> pBlockingLayer(
                new BlockingGraphicLayer(floor->blockingLayer(), *this,
                                         ++zindex));

            QObject::connect(&pBlockingLayer->editorLayer(),
                             SIGNAL(visibilityChanged(bool)),
                             pBlockingLayer.get(), SLOT(setVisibility(bool)));
            QObject::connect(&pBlockingLayer->editorLayer(),
                             SIGNAL(setSelected()), pBlockingLayer.get(),
                             SLOT(setSelected()));

            m_blockingLayers.push_back(std::move(pBlockingLayer));
        }

        // Add event layer
        {
            unique_ptr<EventsGraphicLayer> pEventLayer(
                new EventsGraphicLayer(floor->eventsLayer(), *this, ++zindex));
            m_eventLayers.push_back(std::move(pEventLayer));
        }
    }

    m_drawingTool = nullptr;
}

void MapGraphicsScene::changeMapDocument(
    const std::shared_ptr<MapDocument>& mapDocument)
{
    setMapDocument(mapDocument);
}

void MapGraphicsScene::adjustLayers() const
{
    /*
    if (nullptr != m_paintingLayerState)
    {
        m_paintingLayerState->adjustLayers();
    }
    */
}

void MapGraphicsScene::clearGrid()
{
    Log::info(tr("Clear grid."));
    const int nbCells = m_gridItems.count();
    for (int i = 0; i < nbCells; ++i) {
        removeItem(m_gridItems[i]);
    }
    m_gridItems.clear();
}

void MapGraphicsScene::drawGrid(quint16 width, quint16 height,
                                unsigned int unit)
{
    QPen pen(Qt::black, 0.5);

    clearGrid();

    Log::info(tr("Draw grid."));

    for (int i = 0; i <= width; ++i) {
        QGraphicsItem* item =
            addLine(i * unit, 0, i * unit, unit * height, pen);
        item->setZValue(Z_GRID);
        m_gridItems.push_back(item);
    }

    for (int i = 0; i <= height; ++i) {
        QGraphicsItem* item = addLine(0, i * unit, unit * width, unit * i, pen);
        item->setZValue(Z_GRID);
        m_gridItems.push_back(item);
    }
}

void MapGraphicsScene::redrawGrid()
{
    // m_drawingTool->drawGrid();
}

void MapGraphicsScene::setDrawingTool(::DrawingTools::DrawingTool* drawingTool)
{
    if (nullptr != m_drawingTool) {
        m_drawingTool->onUnselected();
    }
    m_drawingTool = drawingTool;

    if (nullptr != m_currentGraphicLayer) {
        m_currentGraphicLayer->accept(*m_drawingTool);
    }

    Log::info(tr("tool is set."));
    m_drawingTool->drawGrid();
}

void MapGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapMousePressEvent(event);
    }
}

void MapGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapMouseMoveEvent(event);
    }
}

void MapGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapMouseReleaseEvent(event);
    }
}

void MapGraphicsScene::unsetDrawingTool()
{
    if (nullptr != m_drawingTool) {
        m_drawingTool->onUnselected();
    }
    m_drawingTool = nullptr;
}

void MapGraphicsScene::setCurrentGraphicLayer(MapSceneLayer* layer)
{
    Log::info(tr("Set current graphic layer."));
    m_currentGraphicLayer = layer;
    if (nullptr != m_drawingTool) {
        layer->accept(*m_drawingTool);
    }
}

} // namespace GraphicMap
