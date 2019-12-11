#pragma
#include <cstdint>
#include <utility>
#include <vector>

#include <QRect>

#include "layer_clipboard/clipboard.hpp"


namespace GraphicMap {
class BlockingGraphicLayer;
class EventsGraphicLayer;
class VisibleGraphicLayer;
}

namespace LayerClipboard {

class Visible : public Clipboard {
public:
    Visible(
        const QRect&,
        const std::vector<std::pair<std::int8_t, std::int8_t>>&
    );
    Visible(QRect&&, std::vector<std::pair<std::int8_t, std::int8_t>>&&);
private:
    QRect m_clip;
    std::vector<std::pair<std::int8_t, std::int8_t>> m_content;
};

} // namespace LayerClipboard
