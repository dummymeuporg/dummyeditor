#include "graphicMap/eventItemSquare.hpp"

#include <QPainter>

namespace GraphicMap {

EventSquareItem::EventSquareItem()
{}

QRectF EventSquareItem::boundingRect() const {
    return QRectF(0, 0, 16, 16);
}

void EventSquareItem::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QBrush brush(Qt::white);

    painter->setBrush(brush);
    painter->setOpacity(0.5);
    painter->drawRect(0, 0, 16, 16);
}


} // namespace GraphicMap
