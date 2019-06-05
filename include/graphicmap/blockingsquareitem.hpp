#pragma once

#include <QGraphicsItem>
#include <QObject>

namespace GraphicMap {

class BlockingSquareItem : public ::QGraphicsItem
{
public:
    BlockingSquareItem();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;

};

} // namespace GraphicMap
