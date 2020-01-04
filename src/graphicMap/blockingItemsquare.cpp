#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "graphicMap/blockingItemSquare.hpp"

namespace GraphicMap {

BlockingSquareItem::BlockingSquareItem() {}

QRectF BlockingSquareItem::boundingRect() const
{
    return QRectF(0, 0, 8, 8);
}

void BlockingSquareItem::paint(QPainter* painter,
                               const QStyleOptionGraphicsItem* option,
                               QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QBrush brush(Qt::red);

    painter->setBrush(brush);
    painter->setOpacity(0.5);
    painter->drawRect(0, 0, 8, 8);
}


} // namespace GraphicMap
