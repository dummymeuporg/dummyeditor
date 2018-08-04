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

GraphicMap::MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent), m_map(nullptr), m_firstLayer(nullptr),
      m_secondLayer(nullptr), m_thirdLayer(nullptr),
      m_activeLayer(nullptr)
{
    m_state = new GraphicMap::NotPaintingState(*this);
}

GraphicMap::MapGraphicsScene::~MapGraphicsScene() {
    delete m_state;
}

void GraphicMap::MapGraphicsScene::_drawGrid() {

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
    m_state->sceneCleared();

    m_mapDocument = mapDocument;
    m_map = m_mapDocument->map();

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
    return *this;
}

void GraphicMap::MapGraphicsScene::changeMapDocument(
    const std::shared_ptr<Misc::MapDocument>& mapDocument)
{
    setMapDocument(mapDocument);
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
    if(m_map != nullptr && m_chipsetSelection.width() != 0 &&
           m_chipsetSelection.height() != 0 && m_isDrawing)
    {
        QPoint pt = mouseEvent->scenePos().toPoint();
        int tilesWidth = int(m_chipsetSelection.width() / 16);
        int tilesHeight = int(m_chipsetSelection.height() / 16);

        for (int j = 0; j < tilesHeight; ++j) {
            for(int i = 0; i < tilesWidth; ++i) {
                m_activeLayer->setTile(
                         quint16(pt.x() - (pt.x() % 16) + (i * 16)),
                         quint16(pt.y() - (pt.y() % 16) + (j * 16)),
                         qint16(m_chipsetSelection.x() + (i * 16)),
                         qint16(m_chipsetSelection.y() + (j * 16)));
            }
        }
    }
}

void
GraphicMap::MapGraphicsScene::mousePressEvent(
QGraphicsSceneMouseEvent* mouseEvent)
{
    if (mouseEvent->buttons() & Qt::LeftButton) {
        QPoint pt = mouseEvent->scenePos().toPoint();
        m_isDrawing = true;
        qDebug() << m_chipsetSelection;

        if (m_map != nullptr && m_chipsetSelection.width() != 0 &&
            m_chipsetSelection.height() != 0)
        {
            int tilesWidth = int(m_chipsetSelection.width() / 16);
            int tilesHeight = int(m_chipsetSelection.height() / 16);
            qDebug() << tilesWidth << tilesHeight;
            for (int j = 0; j < tilesHeight; ++j) {
                for(int i = 0; i < tilesWidth; ++i) {
                    m_activeLayer->setTile(
                             quint16(pt.x() - (pt.x() % 16) + (i * 16)),
                             quint16(pt.y() - (pt.y() % 16) + (j * 16)),
                             qint16(m_chipsetSelection.x() + (i * 16)),
                             qint16(m_chipsetSelection.y() + (j * 16)));
                }
            }
        }
    }
}

void
GraphicMap::MapGraphicsScene::mouseReleaseEvent(
QGraphicsSceneMouseEvent* mouseEvent)
{
    Q_UNUSED(mouseEvent);
    m_isDrawing = false;
}

void GraphicMap::MapGraphicsScene::changeSelection(const QRect& selection) {
    m_chipsetSelection = selection;
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

