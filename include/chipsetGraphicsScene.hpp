#ifndef CHIPSETGRAPHICSCENE_H
#define CHIPSETGRAPHICSCENE_H

#include <QGraphicsScene>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingTools {
class GraphicPaletteTool;
} // namespace DrawingTools

class QGraphicsPixmapItem;
class QGraphicsSceneMouseEvent;

//////////////////////////////////////////////////////////////////////////////
//  ChipsetGraphicsScene class
//////////////////////////////////////////////////////////////////////////////

class ChipsetGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ChipsetGraphicsScene(QObject* parent = nullptr);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

    QGraphicsPixmapItem* chipset() const { return m_chipset; }

    void setChipset(const QPixmap& pixmap);
    void setChipset(const QString& chipsetPath);
    void setSelection(const QRect& selection);
    void unsetPaletteTool();

private:
    void drawGrid();

signals:
    void selectionChanged(QRect, QPixmap);
    void chipsetChanged(QString);

public slots:
    void setPaletteTool(::DrawingTools::GraphicPaletteTool*);
    void changeChipset(const QString& chipsetPath);

private:
    QGraphicsPixmapItem* m_chipset;
    QRect m_currentSelection;
    DrawingTools::GraphicPaletteTool* m_paletteTool;
};

#endif // CHIPSETGRAPHICSCENE_H
