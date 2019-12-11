#pragma

#include "layer_clipboard/visible.hpp"

namespace GraphicMap {
class BlockingGraphicLayer;
class EventsGraphicLayer;
class VisibleGraphicLayer;
}

namespace LayerClipboard {

Visible::Visible(
    const QRect& clip,
    const std::vector<std::pair<std::int8_t, std::int8_t>>& content
) : m_clip(clip), m_content(content)
{}

Visible::Visible(
    QRect&& clip,
    std::vector<std::pair<std::int8_t, std::int8_t>>&& content
) : m_clip(std::move(clip)), m_content(std::move(content)) {}

} // namespace LayerClipboard
