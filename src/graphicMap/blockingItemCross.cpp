#include "graphicMap/blockingItemCross.hpp"

#include <QPainter>

GraphicMap::BlockingCrossItem::BlockingCrossItem()
{}

QRectF GraphicMap::BlockingCrossItem::boundingRect() const
{
    return QRectF(0, 0, 16, 16);
}

void GraphicMap::BlockingCrossItem::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QBrush brush(Qt::black);

    painter->setBrush(brush);
    painter->drawLine(0, 0, 8, 8);
    painter->drawLine(0, 8, 8, 0);
}
