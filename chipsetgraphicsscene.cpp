#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QRect>

#include "chipsetgraphicscene.h"

ChipsetGraphicsScene::ChipsetGraphicsScene(QObject* parent) :
    QGraphicsScene(parent), m_selectionRectItem(nullptr)
{

}

void
ChipsetGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (mouseEvent->buttons() & Qt::LeftButton) {
        QPoint pt = mouseEvent->scenePos().toPoint();

        QGraphicsScene::mousePressEvent(mouseEvent);

        if (m_selectionRectItem != nullptr) {
            this->removeItem((QGraphicsItem*)m_selectionRectItem);
        }

        // Add a square
        QPen pen(Qt::black, 0.6, Qt::DotLine);
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
