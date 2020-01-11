#include "graphicMap/graphicItem.hpp"

#include <QPainter>

namespace GraphicMap {

GraphicItem::GraphicItem(eGraphicItemType type)
    : m_type(type)
{}

QRectF GraphicItem::boundingRect() const
{
    switch (m_type) {
    case eBlockingCrossItem:
        return QRectF(0, 0, 16, 16);
    case eBlockingSquareItem:
        return QRectF(0, 0, 8, 8);
    case eEventItem:
        return QRectF(0, 0, 16, 16);
    default:
        return QRectF(0, 0, 0, 0);
    }
}

void GraphicItem::paint(QPainter* painter,
                        const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    switch (m_type) {
    case eBlockingCrossItem:
        painter->setBrush(Qt::black);
        painter->drawLine(0, 0, 8, 8);
        painter->drawLine(0, 8, 8, 0);
        break;
    case eBlockingSquareItem:
        painter->setBrush(Qt::red);
        painter->setOpacity(0.5);
        painter->drawRect(0, 0, 8, 8);
        break;
    case eEventItem:
        painter->setBrush(Qt::white);
        painter->setOpacity(0.5);
        painter->drawRect(0, 0, 16, 16);
        break;
    default:
        break;
    }
}
} // namespace GraphicMap
