#ifndef CHIPSETGRAPHICSCENE_H
#define CHIPSETGRAPHICSCENE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>

//////////////////////////////////////////////////////////////////////////////
//  ChipsetGraphicsScene class
//////////////////////////////////////////////////////////////////////////////

class ChipsetGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ChipsetGraphicsScene(QObject* parent = nullptr);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

    const QPixmap& chipset() { return m_chipset; }

public slots:
    void setChipset(const QString& chipsetPath);

private:
    void drawGrid();
    void setSelectRect(const QRect&);

private:
    QPixmap m_chipset;
    QGraphicsRectItem* m_selectionRectItem = nullptr; // Qt deletes it
    bool m_isSelecting                     = false;
    QRect m_currentSelection;
    QPoint m_selectionStart;
};

#endif // CHIPSETGRAPHICSCENE_H
