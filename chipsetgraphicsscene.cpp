#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QRect>
#include <QtGlobal>

#include "chipsetgraphicsscene.h"

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

    quint16 cellsWidth = m_chipset->boundingRect().width() / 16;
    quint16 cellsHeight = m_chipset->boundingRect().height() / 16;

    for (int i = 0; i <= cellsWidth; i++) {
        QGraphicsItem* item = addLine(i*16, 0, i*16, cellsHeight*16, pen);
        item->setZValue(99);
    }

    for (int i = 0; i <= cellsHeight; i++) {
        QGraphicsItem* item = addLine(0, i*16, cellsWidth*16, i*16, pen);
        item->setZValue(99);
    }

}

ChipsetGraphicsScene& ChipsetGraphicsScene::setChipset(const QPixmap& pixmap) {
    clear();
    m_chipset = addPixmap(pixmap);
    _drawGrid();
    return *this;
}

ChipsetGraphicsScene&
ChipsetGraphicsScene::setChipset(const QString& chipsetPath) {
    qDebug() << chipsetPath;
    return setChipset(QPixmap(chipsetPath));
}

void ChipsetGraphicsScene::changeChipset(const QString& chipsetPath) {
    setChipset(chipsetPath);
}

void
ChipsetGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    if (mouseEvent->buttons() & Qt::LeftButton) {
        QPoint pt = mouseEvent->scenePos().toPoint();

        if (pt.x() < m_chipset->boundingRect().width()
            && pt.y() < m_chipset->boundingRect().height())
        {

            QGraphicsScene::mousePressEvent(mouseEvent);

            if (m_selectionRectItem != nullptr) {
                invalidate(m_selectionRectItem->rect());
                this->removeItem(m_selectionRectItem);
            }

            // Add a square
            QPen pen(Qt::red, 2);
            qreal x = pt.x() - (pt.x() % 16);
            qreal y = pt.y() - (pt.y() % 16);
            m_selectionRectItem = addRect(x, y, 16, 16, pen);
        }
    }
}

QRect ChipsetGraphicsScene::selection() const {
    QPoint top_left = m_selectionRectItem->rect().topLeft().toPoint();
    QPoint bottom_right = m_selectionRectItem->rect().bottomRight().toPoint();
    return QRect(top_left / 16, (bottom_right / 16));
}
