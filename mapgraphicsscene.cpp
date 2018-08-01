#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "dummy/layer.h"
#include "dummy/project.h"

#include "mapgraphicsscene.h"

MapGraphicsScene::MapGraphicsScene(QObject* parent)
    : QGraphicsScene(parent), m_map(nullptr)
{

}

void MapGraphicsScene::_drawMap() {

}

void MapGraphicsScene::_drawGrid() {

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

void MapGraphicsScene::_drawLayer(const Dummy::Layer& layer) {

    int i = 0;
    for (auto it = layer.begin(); it != layer.end(); it++, i++) {
        qint16 x = std::get<0>(*it);
        qint16 y = std::get<1>(*it);

        if (x >= 0 && y >= 0) {
            QRect tile(x * 16, y * 16, 16, 16);

            if(nullptr != m_firstLayerItems[i]) {
                removeItem(m_firstLayerItems[i]);
            }

            m_firstLayerItems[i] =
                new QGraphicsPixmapItem(m_mapChipset.copy(tile))
            ;

            qreal posX = (i % m_map->width()) * 16;
            qreal posY = (i / m_map->height()) * 16;
            m_firstLayerItems[i]->setPos(posX, posY);
            //tileItem->setPos(posX, posY);
            //addItem(tileItem);
            addItem(m_firstLayerItems[i]);
        }
    }
}

MapGraphicsScene&
MapGraphicsScene::setMapDocument
(const std::shared_ptr<Misc::MapDocument>& mapDocument)
{

    if (m_map != nullptr) {
        QRect invalidateRegion(0, 0,
                               m_map->width() * 16, m_map->height() * 16);
        qDebug() << "INVALIDATE " << invalidateRegion;
        invalidate(invalidateRegion);
    }

    m_mapDocument = mapDocument;
    m_map = m_mapDocument->map();

    const Dummy::Project& project = m_map->project();

    m_mapChipset = QPixmap(project.fullpath() + "/chipsets/"
                           + m_map->chipset());
    clear();
    _cleanLayer(m_firstLayerItems);
    _cleanLayer(m_secondLayerItems);
    _cleanLayer(m_thirdLayerItems);

    _drawLayer(m_map->firstLayer());
    _drawDarkFilter();
    _drawGrid();

    return *this;
}

void MapGraphicsScene::_cleanLayer(QVector<QGraphicsPixmapItem*>& layer) {
    layer.resize(m_map->width() * m_map->height());
    layer.fill(nullptr);
}

void MapGraphicsScene::changeMapDocument(
    const std::shared_ptr<Misc::MapDocument>& mapDocument)
{
    setMapDocument(mapDocument);
}

void
MapGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if(m_map != nullptr && m_chipsetSelection.width() != 0 &&
           m_chipsetSelection.height() != 0 && m_isDrawing)
    {
        QPoint pt = mouseEvent->scenePos().toPoint();
        int tilesWidth = int(m_chipsetSelection.width() / 16);
        int tilesHeight = int(m_chipsetSelection.height() / 16);

        for (int j = 0; j < tilesHeight; ++j) {
            for(int i = 0; i < tilesWidth; ++i) {
                _setTile(m_firstLayerItems,
                         quint16(pt.x() - (pt.x() % 16) + (i * 16)),
                         quint16(pt.y() - (pt.y() % 16) + (j * 16)),
                         qint16(m_chipsetSelection.x() + (i * 16)),
                         qint16(m_chipsetSelection.y() + (j * 16)));
            }
        }
    }
}

void
MapGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
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
                    _setTile(m_firstLayerItems,
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
MapGraphicsScene::_setTile(QVector<QGraphicsPixmapItem*>& layer,
                           quint16 x,
                           quint16 y,
                           qint16 chipsetX,
                           qint16 chipsetY)
{
    if (x < m_map->width() * 16 && y < m_map->height() * 16)
    {
        int index = (y/16) * m_map->width() + (x/16);

        if (nullptr != layer[index]) {
            removeItem(layer[index]);
        }
        layer[index] = new
            QGraphicsPixmapItem(
                m_mapChipset.copy(QRect(chipsetX, chipsetY, 16, 16)));
        layer[index]->setPos(x, y);
        addItem(layer[index]);
        m_map->firstLayer().setTile(x / 16, y / 16,
                                    chipsetX / 16, chipsetY / 16);
    }
}

void
MapGraphicsScene::_drawDarkFilter() {
    QGraphicsRectItem* darkFilter = new QGraphicsRectItem(sceneRect());
    darkFilter->setBrush(QBrush(QColor(0, 0, 0, 200)));
    darkFilter->setZValue(2);
    addItem(darkFilter);
}

void
MapGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    Q_UNUSED(mouseEvent);
    m_isDrawing = false;
}

void MapGraphicsScene::changeSelection(const QRect& selection) {
    m_chipsetSelection = selection;
}
