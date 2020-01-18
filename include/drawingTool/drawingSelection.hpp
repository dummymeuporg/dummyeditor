#ifndef SELECTION_H
#define SELECTION_H

#include <map>
#include <memory>

#include <QGraphicsRectItem>

#include "drawingTool/drawingTool.hpp"
#include "layer_clipboard/clipboard.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;
class QKeyEvent;

namespace GraphicMap {
class MapSceneLayer;
} // namespace GraphicMap

namespace DrawingTools {

//////////////////////////////////////////////////////////////////////////////
//  DrawingTool class
//////////////////////////////////////////////////////////////////////////////

class SelectionTool : public DrawingTool
{
    Q_OBJECT
public:
    explicit SelectionTool(GraphicMap::MapGraphicsScene&);
    void accept(DrawingVisitor&) override;
    void mapMousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void emitDrawingToolSelected() override;
    void drawGrid() override;

    // GraphicLayerVisitor
    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;

    void doCopy();
    void doCut();
    void doPaste();

signals:
    void drawingToolSelected(::DrawingTools::DrawingTool*);

private:
    void drawSelection();

private:
    bool m_mouseClicked                    = false;
    QGraphicsRectItem* m_selectionRectItem = nullptr;
    QPoint m_startSelection;
    QPoint m_endSelection;
    std::map<GraphicMap::MapSceneLayer*,
             std::shared_ptr<LayerClipboard::Clipboard>>
        m_layers;
};

} // namespace DrawingTools

#endif // SELECTION_H
