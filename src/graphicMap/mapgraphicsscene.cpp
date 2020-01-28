#include "graphicMap/mapGraphicsScene.hpp"

#include "MapTools.hpp"
#include "editor/floor.hpp"
#include "editor/layer.hpp"
#include "graphicMap/layerGraphicBlocking.hpp"
#include "graphicMap/layerGraphicEvents.hpp"
#include "graphicMap/layerGraphicVisible.hpp"
#include "utils/definitions.hpp"

#include <QGraphicsSceneMouseEvent>

using std::unique_ptr;

namespace GraphicMap {

MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{}

MapGraphicsScene::~MapGraphicsScene() {}

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

void MapGraphicsScene::setFloors(const Editor::Floors& mapFloors, const QPixmap& chipset)
{
    // Clear the scene
    clear();

    // Clear the loaded layers
    m_visibleLayers.clear();
    m_blockingLayers.clear();
    m_eventLayers.clear();
    m_currentGraphicLayer = nullptr;

    int zindex = 0;
    for (const auto& floor : mapFloors) {
        instantiateFloor(*floor, chipset, zindex);
    }
}

void MapGraphicsScene::setPreview(const QPixmap& previewPix)
{
    clearPreview();
    m_previewItem = new QGraphicsPixmapItem(previewPix);
}

void MapGraphicsScene::setSelectRect(const QRect& selectionRect)
{
    clearSelectRect();

    QBrush brush(QColor(66, 135, 245));

    m_selectionRectItem = addRect(selectionRect);
    m_selectionRectItem->setZValue(Z_SELEC);
    m_selectionRectItem->setBrush(brush);
    m_selectionRectItem->setOpacity(0.5);
}

void MapGraphicsScene::drawGrid(quint16 width, quint16 height, unsigned int unit)
{
    clearGrid();

    QPen pen(Qt::black, 0.5);

    for (int i = 0; i <= width; ++i) {
        QGraphicsItem* item = addLine(i * unit, 0, i * unit, unit * height, pen);
        item->setZValue(Z_GRID);
        m_gridItems.push_back(item);
    }

    for (int i = 0; i <= height; ++i) {
        QGraphicsItem* item = addLine(0, i * unit, unit * width, unit * i, pen);
        item->setZValue(Z_GRID);
        m_gridItems.push_back(item);
    }
}
void MapGraphicsScene::clear()
{
    clearPreview();
    clearSelectRect();
    clearGrid();
    QGraphicsScene::clear();
}

void MapGraphicsScene::clearPreview()
{
    if (nullptr != m_previewItem) {
        removeItem(m_previewItem);
        m_previewItem = nullptr;
    }
}

void MapGraphicsScene::clearSelectRect()
{
    if (nullptr != m_selectionRectItem) {
        removeItem(m_selectionRectItem);
        m_selectionRectItem = nullptr;
    }
}

void MapGraphicsScene::clearGrid()
{
    const size_t nbCells = m_gridItems.size();

    for (size_t i = 0; i < nbCells; ++i)
        removeItem(m_gridItems[i]);

    m_gridItems.clear();
}

void MapGraphicsScene::instantiateFloor(Editor::Floor& floor, const QPixmap& chipset, int& zindex)
{
    // Add graphic layers
    for (const auto& [position, layer] : floor.graphicLayers()) {
        unique_ptr<VisibleGraphicLayer> pGraphicLayer(new VisibleGraphicLayer(*layer, chipset, ++zindex));
        addItem(pGraphicLayer->graphicItems());
        m_visibleLayers.push_back(std::move(pGraphicLayer));
    }

    // Add 1 blocking layer
    {
        unique_ptr<BlockingGraphicLayer> pBlockingLayer(new BlockingGraphicLayer(floor.blockingLayer(), ++zindex));
        addItem(pBlockingLayer->graphicItems());
        m_blockingLayers.push_back(std::move(pBlockingLayer));
    }

    // Add 1 event layer
    {
        unique_ptr<EventsGraphicLayer> pEventLayer(new EventsGraphicLayer(floor.eventsLayer(), ++zindex));
        addItem(pEventLayer->graphicItems());
        m_eventLayers.push_back(std::move(pEventLayer));
    }
}

void MapGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    if (m_tools == nullptr //
        || ! e->buttons().testFlag(Qt::LeftButton))
        return;

    m_isUsingTool  = true;
    m_firstClickPt = e->scenePos().toPoint();
    m_tools->previewTool(QRect(m_firstClickPt, m_firstClickPt));
}

void MapGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    if (m_tools == nullptr || ! m_isUsingTool)
        return;

    QPoint otherClick = e->scenePos().toPoint();
    m_tools->previewTool(QRect(m_firstClickPt, otherClick));
}

void MapGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    if (m_tools == nullptr || ! m_isUsingTool)
        return;

    m_isUsingTool     = false;
    QPoint otherClick = e->scenePos().toPoint();
    m_tools->useTool(QRect(m_firstClickPt, otherClick));
}

} // namespace GraphicMap
