#ifndef LAYERCLIPBOARD_H
#define LAYERCLIPBOARD_H

#include <QPoint>

#include "graphicmap/graphic_layer_visitor.hpp"

namespace LayerClipboard {

//////////////////////////////////////////////////////////////////////////////
//  Clipboard class
//////////////////////////////////////////////////////////////////////////////

class Clipboard : public GraphicMap::GraphicLayerVisitor {
public:
    Clipboard();

    // XXX: Should not belong here, yet it works.
    const QPoint& target() const { return m_target; }
    void setTarget(const QPoint&);

protected:
    QPoint m_target;
};

} // namespace LayerClipboard

#endif // LAYERCLIPBOARD_H
