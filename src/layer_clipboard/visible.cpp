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
    auto clipIndex(0);
    for (auto j = 0; j < m_clip.height(); j += CELL_H) {
        for (auto i = 0; i < m_clip.width(); i += CELL_W) {
            auto value = m_content.at(clipIndex++);
            layer.setTile(target().x() + i, target().y() + j,
                          value.first * CELL_W, value.second * CELL_H);
        }
    }
}

} // namespace LayerClipboard
