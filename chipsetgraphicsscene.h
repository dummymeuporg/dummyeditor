#ifndef CHIPSETGRAPHICSCENE_H
#define CHIPSETGRAPHICSCENE_H

#include <QGraphicsScene>

#include <memory>

class QGraphicsPixmapItem;
class QGraphicsSceneMouseEvent;

class ChipsetGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ChipsetGraphicsScene(QObject* parent = nullptr);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    QRect selection() const;
    ChipsetGraphicsScene& setChipset(const QPixmap& pixmap);
    ChipsetGraphicsScene& setChipset(const QString& chipsetPath);
    void _drawGrid();

public slots:
    void changeChipset(const QString& chipsetPath);
private:
    QGraphicsRectItem* m_selectionRectItem;
    QGraphicsPixmapItem* m_chipset;
};

#endif // CHIPSETGRAPHICSCENE_H
