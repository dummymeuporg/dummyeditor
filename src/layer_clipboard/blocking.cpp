#include "layer_clipboard/blocking.hpp"

#include "graphicMap/layerGraphicBlocking.hpp"
#include "utils/definitions.hpp"

namespace LayerClipboard {

Blocking::Blocking(const QRect& clip, const std::vector<uint8_t>& content)
    : m_clip(clip)
    , m_content(content)
{}

Blocking::Blocking(QRect&& clip, std::vector<uint8_t>&& content)
    : m_clip(std::move(clip))
    , m_content(std::move(content))
{}

void Blocking::paste(GraphicMap::BlockingGraphicLayer& layer)
{
    // apply clipboard to layer.
    const int clipW  = m_clip.width();
    const int clipH  = m_clip.height();
    size_t clipIndex = 0;

    for (int y = 0; y <= (clipH + BLOCK_H); y += BLOCK_H) {
        for (int x = 0; x <= (clipW + BLOCK_W); x += BLOCK_W) {
            auto value = m_content.at(clipIndex);
            ++clipIndex;
            layer.setTile(target().x() + x, target().y() + y, value);
        }
    }
}

} // namespace LayerClipboard
