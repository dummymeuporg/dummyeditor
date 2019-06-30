#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "core/graphic_layer.hpp"

#include "editor/map.hpp"
#include "editor/project.hpp"

#include "graphicmap/visiblegraphiclayer.hpp"
#include "graphicmap/blockinggraphiclayer.hpp"
#include "graphicmap/mapgraphicsscene.hpp"

#include "graphicmap/nodrawingtool.hpp"
#include "graphicmap/pendrawingtool.hpp"
#include "graphicmap/rectangledrawingtool.hpp"
#include "graphicmap/selectiondrawingtool.hpp"

GraphicMap::MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent),
      m_map(nullptr),
      //m_paintingLayerState(new GraphicMap::NotPaintingState(*this)),
      m_drawingTool(new NoDrawingTool(*this))

{
    //m_paintingLayerState = new GraphicMap::NotPaintingState(*this);
    //m_drawingTool = new NoDrawingTool(*this);
    installEventFilter(this);
}

GraphicMap::MapGraphicsScene::~MapGraphicsScene()
{
    delete m_drawingTool;
    //delete m_paintingLayerState;
}

void GraphicMap::MapGraphicsScene::_drawGrid()
{

    QPen pen(Qt::black, 0.5);

    quint16 width = m_map->width();
    quint16 height = m_map->height();

    for (int i = 0; i <= width; ++i) {
        QGraphicsItem* item = addLine(i * 16, 0, i * 16, 16 * height, pen);
        item->setZValue(99);
    }

    for (int i = 0; i <= height; ++i) {
        QGraphicsItem* item = addLine(0, i * 16, 16 * width, 16 * i, pen);
        item->setZValue(99);
    }

}

GraphicMap::MapGraphicsScene&
GraphicMap::MapGraphicsScene::setMapDocument
(const std::shared_ptr<Misc::MapDocument>& mapDocument)
{

    if (m_map != nullptr) {
        QRect invalidateRegion(0, 0,
                               m_map->width() * 16, m_map->height() * 16);
        qDebug() << "INVALIDATE " << invalidateRegion;
        invalidate(invalidateRegion);
    }
    // Remove the grid.
    clear();


    m_mapDocument = mapDocument;
    m_map = m_mapDocument->map();
    //m_project = m_mapDocument->project();

    //m_paintingLayerState->sceneCleared();

    const Editor::Project& project = m_mapDocument->project();
    m_mapChipset = QPixmap(
        QString(
            (project.coreProject().projectPath()
             / "chipsets"
             / m_map->chipset()
            ).string().c_str())
    );

    m_graphicLayers.clear();
    int zindex = 0;
    for (const auto& level: m_map->levels()) {
        for (const auto& [position, layer]: level->graphicLayers()) {
            m_graphicLayers.push_back(
                std::make_unique<VisibleGraphicLayer>(
                    *this,
                    *layer,
                    m_mapChipset,
                    zindex++
                )
            );
        }

        // Add blocking layer
        /*
        m_graphicLayers.push_back(
            std::make_unique<BlockingGraphicLayer>(
                *this,
                level->blockingLayer(),
                ++zindex
            )
        );
        */
    }

    /*
    m_firstLayer = new VisibleGraphicLayer(
        *this,
        m_map->firstLayer(),
        m_mapChipset,
        1
    );

    m_secondLayer = new VisibleGraphicLayer(
        *this,
        m_map->secondLayer(),
        m_mapChipset,
        3
    );

    m_thirdLayer = new VisibleGraphicLayer(
        *this,
        m_map->thirdLayer(),
        m_mapChipset,
        5
    );

    m_fourthLayer = new VisibleGraphicLayer(
        *this,
        m_map->fourthLayer(),
        m_mapChipset,
        7
    );


    m_blockingLayer = new BlockingGraphicLayer(*this, m_map->blockingLayer());

    m_startingPointLayer = new GraphicMap::StartingPointLayer(*this);
    */

    /*
    m_paintingLayerState->onNewMap();
    m_paintingLayerState->adjustLayers();
    m_paintingLayerState->drawGrid();
    */

    changeSelection(QRect(0,0,0,0));

    return *this;
}

void GraphicMap::MapGraphicsScene::changeMapDocument(
    const std::shared_ptr<Misc::MapDocument>& mapDocument)
{
    setMapDocument(mapDocument);
}

GraphicMap::MapGraphicsScene&
GraphicMap::MapGraphicsScene::setPaitingTool(
    GraphicMap::DrawingTool* tool
)
{
    delete m_drawingTool;
    m_drawingTool = tool;

    if (nullptr != m_mapDocument) {
        m_drawingTool->chipsetSelectionChanged(m_chipsetSelection);
    }

    return *this;
}

void
GraphicMap::MapGraphicsScene::mouseMoveEvent(
    QGraphicsSceneMouseEvent* mouseEvent)
{
    //QGraphicsScene::mouseMoveEvent(mouseEvent);
    if (nullptr != m_mapDocument) {
        m_drawingTool->onMouseMove(mouseEvent);
    }
}

void
GraphicMap::MapGraphicsScene::mousePressEvent(
QGraphicsSceneMouseEvent* mouseEvent)
{
    m_drawingTool->onMousePress(mouseEvent);
}

void
GraphicMap::MapGraphicsScene::mouseReleaseEvent(
QGraphicsSceneMouseEvent* mouseEvent)
{
    m_drawingTool->onMouseRelease(mouseEvent);
}

void GraphicMap::MapGraphicsScene::keyPressEvent(QKeyEvent* keyEvent)
{
    m_drawingTool->onKeyPress(keyEvent);
}

void GraphicMap::MapGraphicsScene::keyReleaseEvent(QKeyEvent* keyEvent)
{
    m_drawingTool->onKeyRelease(keyEvent);
}

void GraphicMap::MapGraphicsScene::changeSelection(const QRect& selection)
{
    m_chipsetSelection = selection;
    if (nullptr != m_mapDocument) {
        m_drawingTool->chipsetSelectionChanged(selection);
    }

}

void GraphicMap::MapGraphicsScene::setPenTool()
{
    qDebug() << "Pen tool enabled";
    setPaitingTool(new GraphicMap::PenDrawingTool(*this));
}

void GraphicMap::MapGraphicsScene::setRectangleTool()
{
    qDebug() << "Rectangle tool enabled";
    setPaitingTool(new GraphicMap::RectangleDrawingTool(*this));
}

void GraphicMap::MapGraphicsScene::setSelectionTool()
{
    qDebug() << "Selection tool enabled";
    setPaitingTool(new GraphicMap::SelectionDrawingTool(*this));
}

bool GraphicMap::MapGraphicsScene::eventFilter(QObject *watched,
                                               QEvent *event)
{
    Q_UNUSED(watched);
    if (event->type() == QEvent::Leave)
    {
        qDebug() << "Mouse left the scene";
        m_drawingTool->onMouseLeave();
    }
    return false;
}

void GraphicMap::MapGraphicsScene::adjustLayers() const {
    /*
    if (nullptr != m_paintingLayerState)
    {
        m_paintingLayerState->adjustLayers();
    }
    */
}
