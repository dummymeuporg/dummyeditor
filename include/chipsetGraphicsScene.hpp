#ifndef CHIPSETGRAPHICSCENE_H
#define CHIPSETGRAPHICSCENE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <memory>

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

    const QPixmap& chipset() const { return m_chipset; }
    const QRect& selectionRect() const { return m_currentSelection; }
    QPixmap selectionPixmap() const;

public slots:
    void setChipset(const QString& chipsetPath);
    void clear();
    void setGridVisible(bool visible = true);

private:
    void drawGrid();
    void setSelectRect(const QRect&);

private:
    QPixmap m_chipset;
    std::unique_ptr<QGraphicsRectItem> m_selectionRectItem;
    std::vector<std::unique_ptr<QGraphicsItem>> m_gridItems;
    bool m_isSelecting = false;
    QRect m_currentSelection;
    QPoint m_selectionStart;
};

#endif // CHIPSETGRAPHICSCENE_H
