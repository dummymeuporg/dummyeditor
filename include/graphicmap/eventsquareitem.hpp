#pragma once

#include <QGraphicsItem>
#include <QObject>

namespace GraphicMap {

class EventSquareItem  : public ::QGraphicsItem {
public:
    EventSquareItem();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;
};

} // namespace GraphicMap
