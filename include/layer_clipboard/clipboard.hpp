#ifndef LAYERCLIPBOARD_H
#define LAYERCLIPBOARD_H

#include <QPoint>

namespace LayerClipboard {

//////////////////////////////////////////////////////////////////////////////
//  Clipboard class
//////////////////////////////////////////////////////////////////////////////

class Clipboard
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
