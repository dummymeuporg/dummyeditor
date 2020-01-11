#include "layer_clipboard/blocking.hpp"

#include "graphicMap/layerGraphicBlocking.hpp"

namespace LayerClipboard {

Blocking::Blocking(const QRect& clip, const std::vector<uint8_t>& content)
    : m_clip(clip)
    , m_content(content)
{}

Blocking::Blocking(QRect&& clip, std::vector<uint8_t>&& content)
    : m_clip(std::move(clip))
    , m_content(std::move(content))
{}

void Blocking::visitGraphicLayer(GraphicMap::BlockingGraphicLayer& layer)
{
    // apply clipboard to layer.
    auto clipIndex(0);
    for (auto j = 0; j <= m_clip.height() + 8; j += 8) {
        for (auto i = 0; i <= m_clip.width() + 8; i += 8) {
            auto value = m_content.at(clipIndex++);
            layer.setTile(target().x() + i, target().y() + j, value);
        }
    }
}

} // namespace LayerClipboard
