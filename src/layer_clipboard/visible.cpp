#include "graphicmap/visiblegraphiclayer.hpp"
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


void Visible::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer) {
    // apply clipboard to layer.
    auto clipIndex(0);
    for (auto j = 0; j < m_clip.height(); j += 16) {
        for (auto i = 0; i < m_clip.width(); i += 16)
        {
            auto value = m_content.at(clipIndex++);
            layer.setTile(
                m_target.x() + i,
                m_target.y() + j,
                value.first * 16,
                value.second * 16
            );
        }
    }
}

} // namespace LayerClipboard
