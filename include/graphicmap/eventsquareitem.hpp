#ifndef EVENTSQUAREITEM_H
#define EVENTSQUAREITEM_H

#include <QGraphicsItem>

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  EventSquareItem class
//////////////////////////////////////////////////////////////////////////////

class EventSquareItem  : public QGraphicsItem {
public:
    EventSquareItem();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;
};

} // namespace GraphicMap

#endif // EVENTSQUAREITEM_H
