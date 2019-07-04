#pragma once

#include <QObject>

class QGraphicsSceneMouseEvent;

namespace DrawingTool {

class DrawingTool : public ::QObject {
public:
    virtual void mousePressEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mouseMoveEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mouseReleaseEvent(::QGraphicsSceneMouseEvent*) = 0;
};

} // namespace DrawingTool
