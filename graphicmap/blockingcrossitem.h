#pragma once

#include <QGraphicsItem>
#include <QObject>


class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

namespace GraphicMap {
    class BlockingCrossItem : public ::QGraphicsItem
    {
    public:
        BlockingCrossItem();

        virtual QRectF boundingRect() const override;
        virtual void paint(QPainter*,
                           const QStyleOptionGraphicsItem*,
                           QWidget* = nullptr) override;
    };
}
