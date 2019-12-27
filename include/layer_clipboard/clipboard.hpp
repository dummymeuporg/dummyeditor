#pragma

#include <QPoint>

#include "graphicmap/graphic_layer_visitor.hpp"

namespace GraphicMap {
class BlockingGraphicLayer;
class EventsGraphicLayer;
class VisibleGraphicLayer;
}

namespace LayerClipboard {

class Clipboard : public GraphicMap::GraphicLayerVisitor {
public:
    Clipboard();

    // XXX: Should not belong here, yet it works.
    const QPoint& target() const {
        return m_target;
    }

    void setTarget(const QPoint&);
protected:
    QPoint m_target;
};

} // namespace LayerClipboard
