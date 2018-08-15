#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "dummy/layer.h"
#include "dummy/project.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"

#include "graphicmap/notpaintingstate.h"
#include "graphicmap/firstlayerstate.h"
#include "graphicmap/secondlayerstate.h"
#include "graphicmap/thirdlayerstate.h"

#include "graphicmap/nodrawingtool.h"
#include "graphicmap/pendrawingtool.h"
#include "graphicmap/rectangledrawingtool.h"
#include "graphicmap/selectiondrawingtool.h"

GraphicMap::MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent), m_map(nullptr), m_firstLayer(nullptr),
      m_secondLayer(nullptr), m_thirdLayer(nullptr),
      m_activeLayer(nullptr)
{
    m_state = new GraphicMap::NotPaintingState(*this);
    m_drawingTool = new NoDrawingTool(*this);
    installEventFilter(this);
}

GraphicMap::MapGraphicsScene::~MapGraphicsScene()
{
    delete m_drawingTool;
    delete m_state;
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
        delete m_firstLayer;
        delete m_secondLayer;
        delete m_thirdLayer;
    }
    // Remove the grid.
    clear();


    m_mapDocument = mapDocument;
    m_map = m_mapDocument->map();

    m_state->sceneCleared();

    const Dummy::Project& project = m_map->project();
    m_mapChipset = QPixmap(project.fullpath() + "/chipsets/"
                           + m_map->chipset());

    m_firstLayer = new
        GraphicMap::GraphicLayer(*this,
                                 m_map->firstLayer(),
                                 m_mapChipset,
                                 1);

    m_secondLayer = new
        GraphicMap::GraphicLayer(*this,
                                 m_map->secondLayer(),
                                 m_mapChipset,
                                 3);

    m_thirdLayer = new
        GraphicMap::GraphicLayer(*this,
                                 m_map->thirdLayer(),
                                 m_mapChipset,
                                 5);

    _drawGrid();
    m_state->onNewMap();
    m_state->adjustLayers();

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

GraphicMap::MapGraphicsScene&
GraphicMap::MapGraphicsScene::setPaitingLayerState(
    GraphicMap::PaintingLayerState* state
)
{
    delete m_state;
    m_state = state;
    state->onNewMap();
    state->adjustLayers();
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

void GraphicMap::MapGraphicsScene::showFirstLayer() {
    qDebug() << "First active layer";
    if (nullptr == m_mapDocument) {
        return;
    }
    setPaitingLayerState(new FirstLayerState(*this));
}

void GraphicMap::MapGraphicsScene::showSecondLayer() {
    qDebug() << "Second active layer";
    if (nullptr == m_mapDocument) {
        return;
    }
    setPaitingLayerState(new SecondLayerState(*this));
}

void GraphicMap::MapGraphicsScene::showThirdLayer() {
    qDebug() << "Third active layer";
    if (nullptr == m_mapDocument) {
        return;
    }
    setPaitingLayerState(new ThirdLayerState(*this));
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
    if (nullptr != m_state)
    {
        m_state->adjustLayers();
    }
}
