#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QIcon>

#include "graphicMap/graphicLayerVisitor.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsSceneMouseEvent;
class QKeyEvent;

namespace GraphicMap {
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTools {
class DrawingVisitor;

//////////////////////////////////////////////////////////////////////////////
//  DrawingTool class
//////////////////////////////////////////////////////////////////////////////

class DrawingTool : public QObject, public GraphicMap::GraphicLayerVisitor
{
    Q_OBJECT
public:
    DrawingTool(GraphicMap::MapGraphicsScene&, QIcon&&);

    virtual void mapMousePressEvent(QGraphicsSceneMouseEvent*)   = 0;
    virtual void mapMouseMoveEvent(QGraphicsSceneMouseEvent*)    = 0;
    virtual void mapMouseReleaseEvent(QGraphicsSceneMouseEvent*) = 0;
    virtual void drawGrid()                                      = 0;
    virtual void onSelected()                                    = 0;
    virtual void onUnselected()                                  = 0;

    const QIcon& icon() const { return m_icon; }

    virtual void accept(DrawingVisitor&) = 0;
    virtual void emitDrawingToolSelected();

public slots:
    void setSelected(bool selected);

signals:
    void drawingToolSelected(DrawingTool*);

protected:
    GraphicMap::MapGraphicsScene& mapGraphScene() { return m_mapGraphicsScene; }

private:
    GraphicMap::MapGraphicsScene& m_mapGraphicsScene;
    QIcon m_icon;
};

} // namespace DrawingTools

#endif // DRAWINGTOOL_H
