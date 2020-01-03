#ifndef BLOCKINGCROSSITEM_H
#define BLOCKINGCROSSITEM_H

#include <QGraphicsItem>

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  BlockingCrossItem class
//////////////////////////////////////////////////////////////////////////////

class BlockingCrossItem : public QGraphicsItem
{
public:
    BlockingCrossItem();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter*, const QStyleOptionGraphicsItem*,
                       QWidget* = nullptr) override;
};
}

#endif // BLOCKINGCROSSITEM_H
