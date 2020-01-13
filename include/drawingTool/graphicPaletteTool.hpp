#ifndef GRAPHICPALETTETOOL_H
#define GRAPHICPALETTETOOL_H

#include "drawingTool/graphicGeneralTool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsRectItem;
class QGraphicsPixmapItem;

class ChipsetGraphicsScene;

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  GraphicPaletteTool class
//////////////////////////////////////////////////////////////////////////////

class GraphicPaletteTool : public GraphicGeneralTool
{
    Q_OBJECT
public:
    GraphicPaletteTool(QIcon&&, GraphicMap::MapGraphicsScene&,
                       GraphicMap::VisibleGraphicLayer* = nullptr);
    void paletteMousePressEvent(QGraphicsSceneMouseEvent*);
    void paletteMouseMoveEvent(QGraphicsSceneMouseEvent*);
    void paletteMouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void emitDrawingToolSelected() override;
    void setSelection(const QRect&, const QPixmap&);
    ChipsetGraphicsScene* chipsetGraphicsScene() const
    {
        return m_chipsetGraphicsScene;
    }
    void setChipsetGraphicsScene(ChipsetGraphicsScene*);
    void onUnselected() override;
    void onSelected() override;

signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTools::GraphicPaletteTool*);

protected:
    QGraphicsPixmapItem* selectionItem() const { return m_selectionItem; }
    void setSelectionItem(QGraphicsPixmapItem* i) { m_selectionItem = i; }
    const QRect& rectSelection() const { return m_rectSelection; }
    const QPixmap& selectionPixmap() const { return m_selectionPixmap; }

private:
    ChipsetGraphicsScene* m_chipsetGraphicsScene = nullptr;
    QGraphicsRectItem* m_selectionRectItem       = nullptr;
    QGraphicsPixmapItem* m_selectionItem         = nullptr;
    bool m_isSelecting                           = false;
    QRect m_rectSelection;
    QPixmap m_selectionPixmap;
    QPoint m_selectionStart;
};

} // namespace DrawingTools

#endif //  GRAPHICPALETTETOOL_H
