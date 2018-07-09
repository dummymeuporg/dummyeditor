#ifndef CHIPSETGRAPHICSCENE_H
#define CHIPSETGRAPHICSCENE_H

#include <QGraphicsScene>

class QGraphicsSceneMouseEvent;

class ChipsetGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ChipsetGraphicsScene(QObject* parent = nullptr);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    QRect selection() const;
private:
    QGraphicsRectItem* m_selectionRectItem;
};

#endif // CHIPSETGRAPHICSCENE_H
