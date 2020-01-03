#ifndef BLOCKINGSQUAREITEM_H
#define BLOCKINGSQUAREITEM_H

#include <QGraphicsItem>

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  BlockingSquareItem class
//////////////////////////////////////////////////////////////////////////////

class BlockingSquareItem : public QGraphicsItem
{
public:
    BlockingSquareItem();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;

};

} // namespace GraphicMap

#endif // BLOCKINGSQUAREITEM_H
