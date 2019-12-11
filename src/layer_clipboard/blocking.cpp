#include "layer_clipboard/blocking.hpp"

namespace GraphicMap {
class BlockingGraphicLayer;
class EventsGraphicLayer;
class VisibleGraphicLayer;
}

namespace LayerClipboard {

Blocking::Blocking(
    const QRect& clip,
    const std::vector<std::uint8_t>& content
) : m_clip(clip), m_content(content)
{}

Blocking::Blocking(
    QRect&& clip,
    std::vector<std::uint8_t>&& content
) : m_clip(std::move(clip)), m_content(std::move(content)) {}

} // namespace LayerClipboard
