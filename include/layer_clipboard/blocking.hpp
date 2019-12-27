#pragma
#include <vector>

#include <QRect>

#include "layer_clipboard/clipboard.hpp"


namespace GraphicMap {
class BlockingGraphicLayer;
class EventsGraphicLayer;
class VisibleGraphicLayer;
}

namespace LayerClipboard {

class Blocking : public Clipboard {
public:
    Blocking(const QRect&, const std::vector<std::uint8_t>&);
    Blocking(QRect&&, std::vector<std::uint8_t>&&);
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;
private:
    QRect m_clip;
    std::vector<std::uint8_t> m_content;
};

} // namespace LayerClipboard
