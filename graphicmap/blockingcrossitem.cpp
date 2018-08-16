#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "graphicmap/blockingcrossitem.h"

GraphicMap::BlockingCrossItem::BlockingCrossItem()
{

}

QRectF GraphicMap::BlockingCrossItem::boundingRect() const
{
    return QRectF(0, 0, 16, 16);
}

void GraphicMap::BlockingCrossItem::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush brush(Qt::black);

    painter->setBrush(brush);
    painter->drawLine(0, 0, 16, 16);
    painter->drawLine(0, 16, 16, 0);
}
