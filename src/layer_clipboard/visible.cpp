#include "layer_clipboard/visible.hpp"

#include "graphicMap/layerGraphicVisible.hpp"

using namespace std;

namespace LayerClipboard {

Visible::Visible(const QRect& clip, const vector<pair<int8_t, int8_t>>& content)
    : m_clip(clip)
    , m_content(content)
{}

Visible::Visible(QRect&& clip, vector<pair<int8_t, int8_t>>&& content)
    : m_clip(move(clip))
    , m_content(move(content))
{}

void Visible::visitGraphicLayer(GraphicMap::VisibleGraphicLayer& layer)
{
    // apply clipboard to layer.
    auto clipIndex(0);
    for (auto j = 0; j < m_clip.height(); j += 16) {
        for (auto i = 0; i < m_clip.width(); i += 16) {
            auto value = m_content.at(clipIndex++);
            layer.setTile(m_target.x() + i, m_target.y() + j, value.first * 16,
                          value.second * 16);
        }
    }
}

} // namespace LayerClipboard
