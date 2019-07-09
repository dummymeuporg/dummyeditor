#ifndef CHIPSETGRAPHICSCENE_H
#define CHIPSETGRAPHICSCENE_H

#include <QGraphicsScene>

#include <memory>

namespace DrawingTool {
namespace Graphic {
class PaletteTool;
} // namespace Graphic
} // namespace DrawingTool

class QGraphicsPixmapItem;
class QGraphicsSceneMouseEvent;

class ChipsetGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ChipsetGraphicsScene(QObject* parent = nullptr);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void setChipset(const QPixmap& pixmap);
    void setChipset(const QString& chipsetPath);
    void _drawGrid();

    inline const QRect& selection() const {
        return m_currentSelection;
    }
    ChipsetGraphicsScene& setSelection(const QRect& selection);
    QGraphicsPixmapItem* chipset() const {
        return m_chipset;
    }

signals:
    void selectionChanged(QRect, QPixmap);
    void chipsetChanged(QString);

public slots:
    void setPaletteTool(::DrawingTool::Graphic::PaletteTool*);
    void changeChipset(const QString& chipsetPath);
private:
    QGraphicsRectItem* m_selectionRectItem;
    QGraphicsPixmapItem* m_chipset;
    QRect m_currentSelection;
    bool m_isSelecting;
    QPoint m_selectionStart;
    DrawingTool::Graphic::PaletteTool* m_paletteTool;
};

#endif // CHIPSETGRAPHICSCENE_H
