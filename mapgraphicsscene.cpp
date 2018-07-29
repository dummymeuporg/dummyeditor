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
            qDebug() << x << y;
            QRect tile(x * 16, y * 16, 16, 16);
            QGraphicsPixmapItem* tileItem = new
                QGraphicsPixmapItem(m_mapChipset.copy(tile));

            qreal posX = (i % m_map->width()) * 16;
            qreal posY = (i / m_map->height()) * 16;
            tileItem->setPos(posX, posY);
            addItem(tileItem);
        }
    }
}

MapGraphicsScene&
MapGraphicsScene::setMap(const std::shared_ptr<Dummy::Map>& map) {

    if (m_map != nullptr) {
        QRect invalidateRegion(0, 0,
                               m_map->width() * 16, m_map->height() * 16);
        qDebug() << invalidateRegion;
        invalidate(invalidateRegion);
    }

    m_map = map;
    const Dummy::Project& project = m_map->project();

    m_mapChipset = QPixmap(project.fullpath() + "/chipsets/"
                           + m_map->chipset());
    clear();

    _drawLayer(m_map->firstLayer());
    _drawGrid();

    return *this;
}

void MapGraphicsScene::changeMap(const std::shared_ptr<Dummy::Map>& map) {
    setMap(map);
}

void
MapGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if(m_map != nullptr && m_chipsetSelection.width() != 0 &&
           m_chipsetSelection.height() != 0 && m_isDrawing)
    {
        QPoint pt = mouseEvent->scenePos().toPoint();
        _setTile(pt.x() - (pt.x() % 16), pt.y() - (pt.y() % 16));
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
            _setTile(pt.x() - (pt.x() % 16), pt.y() - (pt.y() % 16));
        }
    }
}

void
MapGraphicsScene::_setTile(qreal x, qreal y) {

    if (x >= 0 && y >= 0
        && x < m_map->width() * 16 && y < m_map->height() * 16)
    {
        QGraphicsPixmapItem* pixmapItem = new
            QGraphicsPixmapItem(m_mapChipset.copy(m_chipsetSelection));
        pixmapItem->setPos(x, y);
        addItem(pixmapItem);
        m_map->firstLayer().setTile(
            x / 16, y / 16,
            m_chipsetSelection.x()/16, m_chipsetSelection.y()/16);
    }
}

void
MapGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    Q_UNUSED(mouseEvent);
    m_isDrawing = false;
}

void MapGraphicsScene::changeSelection(const QRect& selection) {
    m_chipsetSelection = selection;
}
