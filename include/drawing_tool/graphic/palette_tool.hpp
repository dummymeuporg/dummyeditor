#ifndef GRAPHICPALETTETOOL_H
#define GRAPHICPALETTETOOL_H

#include "drawing_tool/graphic/graphic_tool.hpp"

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsRectItem;
class QGraphicsPixmapItem;

namespace DrawingTools {
namespace Graphic {

//////////////////////////////////////////////////////////////////////////////
//  GraphicTool class
//////////////////////////////////////////////////////////////////////////////

class GraphicPaletteTool : public GraphicTool {
    Q_OBJECT
public:
    GraphicPaletteTool(
        QIcon&&,
        GraphicMap::MapGraphicsScene&,
        GraphicMap::VisibleGraphicLayer* = nullptr
    );
    void paletteMousePressEvent(QGraphicsSceneMouseEvent*);
    void paletteMouseMoveEvent(QGraphicsSceneMouseEvent*);
    void paletteMouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void emitDrawingToolSelected() override;
    void setSelection(const QRect&, const QPixmap&);
    ChipsetGraphicsScene* chipsetGraphicsScene() const {
        return m_chipsetGraphicsScene;
    }
    void setChipsetGraphicsScene(::ChipsetGraphicsScene*);
    void onUnselected() override;
    void onSelected() override;

signals:
    // Note: I have to put the whole namespace shit here, because Qt
    // signals/slots framework is based on textual comparison.
    void drawingToolSelected(::DrawingTools::Graphic::GraphicPaletteTool*);

protected:
    ChipsetGraphicsScene* m_chipsetGraphicsScene;
    QRect m_rectSelection;
    QPixmap m_selectionPixmap;
    QGraphicsRectItem* m_selectionRectItem;
    QGraphicsPixmapItem* m_selectionItem;
    bool m_isSelecting;
    QPoint m_selectionStart;
};

} // namespace Graphic
} // namespace DrawingTools

#endif GRAPHICPALETTETOOL_H
