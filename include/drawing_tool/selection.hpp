#ifndef SELECTION_H
#define SELECTION_H

#include <map>

#include <QGraphicsRectItem>

#include "drawing_tool/drawing_tool.hpp"
#include "layer_clipboard/clipboard.hpp"

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  DrawingTool class
//////////////////////////////////////////////////////////////////////////////

class Selection : public DrawingTool {
    Q_OBJECT
public:
    Selection(GraphicMap::MapGraphicsScene&);
    void accept(Visitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void mapKeyPressEvent(QKeyEvent*) override;
    void mapKeyReleaseEvent(QKeyEvent*) override;
    void mapMouseLeaveEvent() override;
    void emitDrawingToolSelected() override;
    void drawGrid() override;
    void onSelected() override;
    void onUnselected() override;

    // GraphicLayerVisitor
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
    void onCopyKeyPressed();

private:
    void drawSelection();
    void onCopyKeyPressed(QKeyEvent*);
    void onCutKeyPressed(QKeyEvent*);
    void onPasteKeyPressed(QKeyEvent*);

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    bool m_mouseClicked;
    QGraphicsRectItem* m_selectionRectItem;
    QPoint m_startSelection;
    QPoint m_endSelection;
    std::map<GraphicMap::GraphicLayer*,
             std::shared_ptr<LayerClipboard::Clipboard>> m_layers;
};

} // namespace DrawingTool

#endif // SELECTION_H
