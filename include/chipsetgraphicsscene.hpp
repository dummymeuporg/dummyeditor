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
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);
    ChipsetGraphicsScene& setChipset(const QPixmap& pixmap);
    ChipsetGraphicsScene& setChipset(const QString& chipsetPath);
    void _drawGrid();

    inline const QRect& selection() const {
        return m_currentSelection;
    }
    ChipsetGraphicsScene& setSelection(const QRect& selection) {
        m_currentSelection = selection;
        emit selectionChanged(m_currentSelection);
        return *this;
    }

signals:
    void selectionChanged(const QRect&);
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
