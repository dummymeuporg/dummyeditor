#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QIcon>

#include "graphicMap/graphicLayerVisitor.hpp"
#include "widget_drawingToolbar/widget.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;
class QKeyEvent;

namespace GraphicMap {
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTools {
class Visitor;

//////////////////////////////////////////////////////////////////////////////
//  DrawingTool class
//////////////////////////////////////////////////////////////////////////////

class DrawingTool : public QObject, public GraphicMap::GraphicLayerVisitor {
    Q_OBJECT
public:
    DrawingTool(GraphicMap::MapGraphicsScene&, QIcon&&);

    virtual void mapMousePressEvent(QGraphicsSceneMouseEvent*) = 0;
    virtual void mapMouseMoveEvent(QGraphicsSceneMouseEvent*) = 0;
    virtual void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) = 0;
    virtual void mapKeyPressEvent(QKeyEvent*) = 0;
    virtual void mapKeyReleaseEvent(QKeyEvent*) = 0;
    virtual void mapMouseLeaveEvent() = 0;
    virtual void drawGrid() = 0;
    virtual void onSelected() = 0;
    virtual void onUnselected() = 0;

    const QIcon& icon() const { return m_icon; }

    virtual void accept(Visitor&) = 0;
    virtual void emitDrawingToolSelected();

    void setSelected(bool selected);

signals:
    void drawingToolSelected(DrawingTool*);

protected:
    GraphicMap::MapGraphicsScene& m_mapGraphicsScene;

private:
    QIcon m_icon;
};

} // namespace DrawingTool

#endif // DRAWINGTOOL_H
