#include "layer_clipboard/clipboard.hpp"

namespace LayerClipboard {

Clipboard::Clipboard() {}

void Clipboard::setTarget(const QPoint& target)
{
    m_target = target;
}

} // namespace LayerClipboard
