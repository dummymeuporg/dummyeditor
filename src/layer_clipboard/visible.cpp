#include "layer_clipboard/visible.hpp"

#include "definitions.hpp"
#include "graphicMap/layerGraphicVisible.hpp"

using std::pair;
using std::vector;

namespace LayerClipboard {

Visible::Visible(const QRect& clip, const vector<pair<int8_t, int8_t>>& content)
    : m_clip(clip)
    , m_content(content)
{}

Visible::Visible(QRect&& clip, vector<pair<int8_t, int8_t>>&& content)
    : m_clip(std::move(clip))
    , m_content(std::move(content))
{}

void Visible::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer)
{
    // apply clipboard to layer.
    const int clipW  = m_clip.width();
    const int clipH  = m_clip.height();
    size_t clipIndex = 0;

    for (int y = 0; y < clipH; y += CELL_H) {
        for (int x = 0; x < clipW; x += CELL_W) {
            auto value = m_content.at(clipIndex++);
            layer.setTile(target().x() + x, target().y() + y,
                          value.first * CELL_W, value.second * CELL_H);
        }
    }
}

} // namespace LayerClipboard
