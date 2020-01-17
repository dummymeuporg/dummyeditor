#include "graphicMap/graphicItem.hpp"

#include <QPainter>

#include "definitions.hpp"

namespace GraphicMap {

GraphicItem::GraphicItem(eGraphicItemType type)
    : m_type(type)
{}

QRectF GraphicItem::boundingRect() const
{
    switch (m_type) {
    case eGraphicItemType::eBlockingCross:
        return QRectF(0, 0, CELL_W, CELL_H);
    case eGraphicItemType::eBlockingSquare:
        return QRectF(0, 0, BLOCK_W, BLOCK_H);
    case eGraphicItemType::eEvent:
        return QRectF(0, 0, CELL_W, CELL_H);
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
    case eGraphicItemType::eBlockingCross:
        painter->setBrush(Qt::black);
        painter->drawLine(0, 0, BLOCK_W, BLOCK_H);
        painter->drawLine(0, BLOCK_H, BLOCK_W, 0);
        break;
    case eGraphicItemType::eBlockingSquare:
        painter->setBrush(Qt::red);
        painter->setOpacity(0.5);
        painter->drawRect(0, 0, BLOCK_W, BLOCK_H);
        break;
    case eGraphicItemType::eEvent:
        painter->setBrush(Qt::white);
        painter->setOpacity(0.5);
        painter->drawRect(0, 0, CELL_W, CELL_H);
        break;
    default:
        break;
    }
}
} // namespace GraphicMap
