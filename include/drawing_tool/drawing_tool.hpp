#pragma once

#include <QIcon>
#include <QObject>

#include "widget/drawing_toolbar/widget.hpp"

class QGraphicsSceneMouseEvent;
class QKeyEvent;

namespace GraphicMap {
class MapGraphicsScene;
} // namespace GraphicMap

namespace DrawingTool {

class Visitor;

class DrawingTool : public ::QObject {
    Q_OBJECT
public:
    DrawingTool(GraphicMap::MapGraphicsScene&, QIcon&&);
    virtual void mapMousePressEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mapMouseMoveEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mapMouseReleaseEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mapKeyPressEvent(::QKeyEvent*) = 0;
    virtual void mapKeyReleaseEvent(::QKeyEvent*) = 0;

    const QIcon& icon() const {
        return m_icon;
    }

    virtual void accept(Visitor&) = 0;
    virtual void emitDrawingToolSelected();

    void setSelected(bool selected);

signals:
    void drawingToolSelected(DrawingTool*);
private:
    GraphicMap::MapGraphicsScene& m_mapGraphicsScene;
    QIcon m_icon;
};

} // namespace DrawingTool
