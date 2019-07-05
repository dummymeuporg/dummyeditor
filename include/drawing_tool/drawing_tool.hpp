#pragma once

#include <QIcon>
#include <QObject>

class QGraphicsSceneMouseEvent;

namespace DrawingTool {

class DrawingTool : public ::QObject {
public:
    DrawingTool(QIcon&&);
    virtual void mousePressEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mouseMoveEvent(::QGraphicsSceneMouseEvent*) = 0;
    virtual void mouseReleaseEvent(::QGraphicsSceneMouseEvent*) = 0;

    const QIcon& icon() const {
        return m_icon;
    }
private:
    QIcon m_icon;
};

} // namespace DrawingTool
