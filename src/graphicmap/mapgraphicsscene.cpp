#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include <dummy/core/graphic_layer.hpp>

#include "editor/map.hpp"
#include "editor/project.hpp"

#include "graphicmap/visiblegraphiclayer.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/eventsgraphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"


namespace GraphicMap {

MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent),
      m_mapDocument(nullptr),
      m_map(nullptr),
      m_isDrawing(false),
      m_drawingTool(nullptr),
      m_currentGraphicLayer(nullptr)

{
    //m_paintingLayerState = new GraphicMap::NotPaintingState(*this);
    //m_drawingTool = new NoDrawingTool(*this);
    installEventFilter(this);
}

MapGraphicsScene::~MapGraphicsScene()
{
    //delete m_drawingTool;
    //delete m_paintingLayerState;
}

MapGraphicsScene& MapGraphicsScene::setMapDocument
(const std::shared_ptr<Misc::MapDocument>& mapDocument) {
    if (m_map != nullptr) {
        QRect invalidateRegion(0, 0,
                               m_map->width() * 16, m_map->height() * 16);
        qDebug() << "INVALIDATE " << invalidateRegion;
        invalidate(invalidateRegion);

        for (auto& graphicLayer: m_graphicLayers) {
            QObject::disconnect(
                &graphicLayer->editorLayer(),
                SIGNAL(visibilityChanged(bool)),
                graphicLayer,
                SLOT(setVisibility(bool))
            );
        }

    }
    // Clear the scene
    clearGrid();
    clear();

    m_mapDocument = mapDocument;
    m_map = m_mapDocument->map();

    const Editor::Project& project = m_mapDocument->project();
    m_mapChipset = QPixmap(
        QString(
            (project.coreProject().projectPath()
             / "chipsets"
             / m_map->chipset()
            ).string().c_str())
    );

    m_currentGraphicLayer = nullptr;
    for (auto& graphicLayer: m_graphicLayers) {
        delete graphicLayer;
    }
    m_graphicLayers.clear();

    int zindex = 0;
    for (const auto& floor: m_map->floors()) {
        for (const auto& [position, layer]: floor->graphicLayers()) {
            qDebug() << "Position: " << position;

            auto graphicLayer = new VisibleGraphicLayer(
                *layer,
                *this,
                m_mapChipset,
                zindex++
            );

            m_graphicLayers.push_back(graphicLayer);

            QObject::connect(
                &graphicLayer->editorLayer(),
                SIGNAL(visibilityChanged(bool)),
                graphicLayer,
                SLOT(setVisibility(bool))
            );

            QObject::connect(
                &graphicLayer->editorLayer(),
                SIGNAL(setSelected()),
                graphicLayer,
                SLOT(setSelected())
            );
        }

        // Add blocking layer
        auto graphicLayer = new BlockingGraphicLayer(
            floor->blockingLayer(),
            *this,
            ++zindex
        );

        // Add event layer
        auto eventLayer = new EventsGraphicLayer(
            floor->eventsLayer(),
            *this,
            ++zindex
        );

        m_graphicLayers.push_back(graphicLayer);

        QObject::connect(
            &graphicLayer->editorLayer(),
            SIGNAL(visibilityChanged(bool)),
            graphicLayer,
            SLOT(setVisibility(bool))
        );
        QObject::connect(
            &graphicLayer->editorLayer(),
            SIGNAL(setSelected()),
            graphicLayer,
            SLOT(setSelected())
        );
    }

    //changeSelection(QRect(0,0,0,0));
    m_drawingTool = nullptr;
    return *this;
}

void MapGraphicsScene::changeMapDocument(
    const std::shared_ptr<Misc::MapDocument>& mapDocument
) {
    setMapDocument(mapDocument);
}

void MapGraphicsScene::adjustLayers() const {
    /*
    if (nullptr != m_paintingLayerState)
    {
        m_paintingLayerState->adjustLayers();
    }
    */
}

void MapGraphicsScene::clearGrid() {
    qDebug() << "Clear grid.";
    for (auto it = m_gridItems.begin(); it != m_gridItems.end(); ++it) {
        removeItem(*it);
    }
    m_gridItems.clear();
}

void MapGraphicsScene::drawGrid(
    quint16 width,
    quint16 height,
    unsigned int unit)
{
    QPen pen(Qt::black, 0.5);

    clearGrid();

    qDebug() << "Draw grid.";

    for (int i = 0; i <= width; ++i) {
        QGraphicsItem* item = addLine(
            i * unit, 0,
            i * unit,
            unit * height,
            pen
        );
        item->setZValue(88888);
        m_gridItems.push_back(item);
    }

    for (int i = 0; i <= height; ++i) {
        QGraphicsItem* item = addLine(
            0,
            i * unit,
            unit * width,
            unit * i,
            pen
        );
        item->setZValue(88888);
        m_gridItems.push_back(item);
    }
}

void MapGraphicsScene::redrawGrid() {
    //m_drawingTool->drawGrid();
}

void MapGraphicsScene::setDrawingTool(::DrawingTool::DrawingTool* drawingTool)
{
    if (nullptr != m_drawingTool) {
        m_drawingTool->onUnselected();
    }
    m_drawingTool = drawingTool;

    if (nullptr != m_currentGraphicLayer) {
        m_currentGraphicLayer->accept(*m_drawingTool);
    }

    qDebug() << "tool is set.";
    m_drawingTool->drawGrid();
}

void MapGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapMousePressEvent(event);
    }
}

void MapGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapMouseMoveEvent(event);
    }
}

void MapGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapMouseReleaseEvent(event);
    }
}

void MapGraphicsScene::keyPressEvent(QKeyEvent* event) {
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapKeyPressEvent(event);
    }
}

void MapGraphicsScene::keyReleaseEvent(QKeyEvent* event) {
    if (nullptr != m_drawingTool) {
        m_drawingTool->mapKeyReleaseEvent(event);
    }
}

void MapGraphicsScene::unsetDrawingTool() {
    if (nullptr != m_drawingTool) {
        m_drawingTool->onUnselected();
    }
    m_drawingTool = nullptr;
}

bool MapGraphicsScene::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)
    if (event->type() == QEvent::Leave)
    {
        qDebug() << "Mouse left the scene";
        if (nullptr != m_drawingTool) {
            m_drawingTool->mapMouseLeaveEvent();
        }
    }
    return false;
}

void MapGraphicsScene::setCurrentGraphicLayer(GraphicLayer* layer) {
    qDebug() << "Set current graphic layer.";
    m_currentGraphicLayer = layer;
    if (nullptr != m_drawingTool) {
        layer->accept(*m_drawingTool);
    }
}

} // namespace GraphicMap
