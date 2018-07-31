#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QRect>
#include <QtGlobal>

#include "chipsetgraphicsscene.h"

ChipsetGraphicsScene::ChipsetGraphicsScene(QObject* parent) :
    QGraphicsScene(parent), m_selectionRectItem(nullptr), m_chipset(nullptr),
    m_isSelecting(false)
{
    if (m_chipset) {
        _drawGrid();
    }
}

void
ChipsetGraphicsScene::_drawGrid() {
    QPen pen(Qt::black, 0.5);

    quint16 cellsWidth = static_cast<quint16>(
        m_chipset->boundingRect().width() / 16);
    quint16 cellsHeight = static_cast<quint16>(
        m_chipset->boundingRect().height() / 16);

    for (int i = 0; i <= cellsWidth; i++) {
        QGraphicsItem* item = addLine(i*16, 0, i*16, cellsHeight*16, pen);
        item->setZValue(99);
    }

    for (int i = 0; i <= cellsHeight; i++) {
        QGraphicsItem* item = addLine(0, i*16, cellsWidth*16, i*16, pen);
        item->setZValue(99);
    }

    m_selectionRectItem = nullptr;

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
    setSelection(QRect(0, 0, 0, 0));
    return setChipset(QPixmap(chipsetPath));
}

void ChipsetGraphicsScene::changeChipset(const QString& chipsetPath) {
    setChipset(chipsetPath);
}

void
ChipsetGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    m_isSelecting = false;
}

void
ChipsetGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    if (m_isSelecting) {
        QPoint pt = mouseEvent->scenePos().toPoint();

        if (m_selectionRectItem != nullptr) {
            removeItem(m_selectionRectItem);
            m_selectionRectItem = nullptr;
        }

        QPen pen(Qt::red, 2);

        qreal x = m_selectionStart.x() - (m_selectionStart.x() % 16);
        qreal y = m_selectionStart.y() - (m_selectionStart.y() % 16);
        qreal xEnd = pt.x() + (16 - (pt.x() % 16));
        qreal yEnd = pt.y() + (16 - (pt.y() % 16));

        if (pt.x() >= m_selectionStart.x()
            && pt.y() >= m_selectionStart.y())
        {
            qDebug() << x << y << xEnd << yEnd;
            setSelection(QRect(x, y, xEnd - x, yEnd - y));
            m_selectionRectItem = addRect(m_currentSelection, pen);
        }

    }
}

void
ChipsetGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    QGraphicsScene::mousePressEvent(mouseEvent);
    if (mouseEvent->buttons() & Qt::LeftButton) {
        m_isSelecting = true;
        m_selectionStart = mouseEvent->scenePos().toPoint();

        if (m_selectionStart.x() < m_chipset->boundingRect().width()
            && m_selectionStart.y() < m_chipset->boundingRect().height())
        {
            if (m_selectionRectItem != nullptr) {
                invalidate(m_selectionRectItem->rect());
                this->removeItem(m_selectionRectItem);
            }

            // Add a square
            QPen pen(Qt::red, 2);
            qreal x = m_selectionStart.x() - (m_selectionStart.x() % 16);
            qreal y = m_selectionStart.y() - (m_selectionStart.y() % 16);
            setSelection(QRect(x, y, 16, 16));
            m_selectionRectItem = addRect(m_currentSelection, pen);
        }

    }
}
