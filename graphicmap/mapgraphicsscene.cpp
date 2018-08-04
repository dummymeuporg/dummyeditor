#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "dummy/layer.h"
#include "dummy/project.h"

#include "graphicmap/graphiclayer.h"
#include "graphicmap/mapgraphicsscene.h"

GraphicMap::MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent), m_map(nullptr), m_firstLayer(nullptr),
      m_secondLayer(nullptr), m_thirdLayer(nullptr), m_currentLayer(1),
      m_activeLayer(nullptr)
{

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
        delete m_darkFilterOne;
        delete m_secondLayer;
        delete m_darkFilterTwo;
        delete m_thirdLayer;
    }
    // Remove the grid.
    clear();

    m_mapDocument = mapDocument;
    m_map = m_mapDocument->map();
    QRect mapRect(0, 0, m_map->width()*16, m_map->height()*16);
    const Dummy::Project& project = m_map->project();
    m_mapChipset = QPixmap(project.fullpath() + "/chipsets/"
                           + m_map->chipset());

    qDebug() << "Active layer = " << m_currentLayer;
    m_firstLayer = new
        GraphicMap::GraphicLayer(*this,
                                 m_map->firstLayer(),
                                 m_mapChipset,
                                 1);
    m_darkFilterOne = new QGraphicsRectItem(mapRect);
    m_darkFilterOne->setBrush(QBrush(QColor(0, 0, 0, 127)));

    m_darkFilterOne->setZValue(2);


    m_secondLayer = new
        GraphicMap::GraphicLayer(*this,
                                 m_map->secondLayer(),
                                 m_mapChipset,
                                 3);

    m_darkFilterTwo = new QGraphicsRectItem(mapRect);
    m_darkFilterTwo->setBrush(QBrush(QColor(0, 0, 0, 127)));

    m_darkFilterTwo->setZValue(4);


    m_thirdLayer = new
        GraphicMap::GraphicLayer(*this,
                                 m_map->thirdLayer(),
                                 m_mapChipset,
                                 5);


    // XXX: Ugly
    if (m_currentLayer == 1) {
        m_secondLayer->setOpacity(0.5);
        m_thirdLayer->setOpacity(0.25);
    } else if(m_currentLayer == 2) {
        m_secondLayer->setOpacity(1);
        m_thirdLayer->setOpacity(0.5);
    } else if (m_currentLayer == 3) {
        m_secondLayer->setOpacity(1);
        m_thirdLayer->setOpacity(1);
    }

    addItem(m_darkFilterOne);
    addItem(m_darkFilterTwo);

    m_darkFilterOne->setVisible(m_currentLayer >= 2);
    m_darkFilterTwo->setVisible(m_currentLayer == 3);


    _drawGrid();

    return *this;
}

void GraphicMap::MapGraphicsScene::changeMapDocument(
    const std::shared_ptr<Misc::MapDocument>& mapDocument)
{
    setMapDocument(mapDocument);
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
    m_activeLayer = m_firstLayer;
    m_currentLayer = 1;
    m_darkFilterOne->setVisible(false);
    m_secondLayer->setOpacity(0.5);
    m_darkFilterTwo->setVisible(false);
    m_thirdLayer->setOpacity(0.25);
}

void GraphicMap::MapGraphicsScene::showSecondLayer() {
    qDebug() << "Second active layer";
    if (nullptr == m_mapDocument) {
        return;
    }
    m_activeLayer = m_secondLayer;
    m_currentLayer = 2;
    m_darkFilterOne->setVisible(true);
    m_secondLayer->setOpacity(1);
    m_darkFilterTwo->setVisible(false);
    m_thirdLayer->setOpacity(0.5);
}

void GraphicMap::MapGraphicsScene::showThirdLayer() {
    qDebug() << "Third active layer";
    if (nullptr == m_mapDocument) {
        return;
    }
    m_activeLayer = m_thirdLayer;
    m_currentLayer = 3;
    m_darkFilterOne->setVisible(true);
    m_darkFilterTwo->setVisible(true);
    m_secondLayer->setOpacity(1);
    m_thirdLayer->setOpacity(1);
}

