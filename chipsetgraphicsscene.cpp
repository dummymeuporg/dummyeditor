#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QRect>

#include "chipsetgraphicscene.h"

ChipsetGraphicsScene::ChipsetGraphicsScene(QObject* parent) :
    QGraphicsScene(parent), m_selectionRectItem(nullptr), m_chipset(nullptr)
{
    if (m_chipset) {
        _drawGrid();
    }
}

void
ChipsetGraphicsScene::_drawGrid() {
    QPen pen(Qt::black, 0.5);
    for (int i = 0; i < 58; i++) {
        QGraphicsItem* item = addLine(i*16, 0, i*16, 16*16, pen);
        item->setZValue(99);
    }

    for (int i = 0; i < 17; i++) {
        QGraphicsItem* item = addLine(0, i*16, 57*16, i*16, pen);
        item->setZValue(99);
    }
}

ChipsetGraphicsScene& ChipsetGraphicsScene::setChipset(const QPixmap& pixmap) {
    clear();
    if(nullptr != m_chipset) {

        removeItem(m_chipset);

    }

    m_chipset = addPixmap(pixmap);
    _drawGrid();
    return *this;
}

ChipsetGraphicsScene&
ChipsetGraphicsScene::setChipset(const QString& chipsetPath) {
    qDebug() << chipsetPath;
    return setChipset(QPixmap(chipsetPath));
}

void
ChipsetGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (mouseEvent->buttons() & Qt::LeftButton) {
        QPoint pt = mouseEvent->scenePos().toPoint();

        QGraphicsScene::mousePressEvent(mouseEvent);

        if (m_selectionRectItem != nullptr) {
            this->removeItem(m_selectionRectItem);
        }

        // Add a square
        QPen pen(Qt::red, 1);
        qreal x = pt.x() - (pt.x() % 16);
        qreal y = pt.y() - (pt.y() % 16);
        m_selectionRectItem = addRect(x, y, 16, 16, pen);
    }
}

QRect ChipsetGraphicsScene::selection() const {
    QPoint top_left = m_selectionRectItem->rect().topLeft().toPoint();
    QPoint bottom_right = m_selectionRectItem->rect().bottomRight().toPoint();
    return QRect(top_left / 16, (bottom_right / 16));
}
