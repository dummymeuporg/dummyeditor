#ifndef LAYERCLIPBOARD_H
#define LAYERCLIPBOARD_H

#include <QPoint>

#include "graphicMap/graphicLayerVisitor.hpp"

namespace LayerClipboard {

//////////////////////////////////////////////////////////////////////////////
//  Clipboard class
//////////////////////////////////////////////////////////////////////////////

class Clipboard : public GraphicMap::GraphicLayerVisitor
{
public:
    Clipboard();

    // XXX: Should not belong here, yet it works.
    const QPoint& target() const { return m_target; }
    void setTarget(const QPoint&);

private:
    QPoint m_target = QPoint(0, 0);
};

} // namespace LayerClipboard

#endif // LAYERCLIPBOARD_H
