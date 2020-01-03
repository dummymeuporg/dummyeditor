#include "layer_clipboard/clipboard.hpp"

namespace LayerClipboard {

Clipboard::Clipboard()
    : m_target(0, 0)
{}

void Clipboard::setTarget(const QPoint& target) {
    m_target = target;
}

} // namespace LayerClipboard
