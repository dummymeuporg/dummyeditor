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

class DrawingTool : public ::QObject {
public:
    DrawingTool(GraphicMap::MapGraphicsScene&, QIcon&&);
    virtual void mousePressEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mouseMoveEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mouseReleaseEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void keyPressEvent(::QKeyEvent*) = 0;
    virtual void keyReleaseEvent(::QKeyEvent*) = 0;

    const QIcon& icon() const {
        return m_icon;
    }
private:
    GraphicMap::MapGraphicsScene& m_mapGraphicsScene;
    QIcon m_icon;
};

} // namespace DrawingTool
