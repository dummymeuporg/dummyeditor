#ifndef CHIPSETGRAPHICSCENE_H
#define CHIPSETGRAPHICSCENE_H

#include <QGraphicsScene>

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace DrawingTools {
class GraphicPaletteTool;
} // namespace DrawingTools

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

    QGraphicsPixmapItem* chipset() const { return m_chipset; }

    void setChipset(const QPixmap& pixmap);
    void setChipset(const QString& chipsetPath);
    void setSelection(const QRect& selection);
    void unsetPaletteTool();

public slots:
    void setPaletteTool(::DrawingTools::GraphicPaletteTool*);
    void changeChipset(const QString& chipsetPath);

signals:
    void selectionChanged(QRect, QPixmap);
    void chipsetChanged(QString);

private:
    void drawGrid();

private:
    QGraphicsPixmapItem* m_chipset = nullptr;
    QRect m_currentSelection;
    DrawingTools::GraphicPaletteTool* m_paletteTool = nullptr;
};

#endif // CHIPSETGRAPHICSCENE_H
