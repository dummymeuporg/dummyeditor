#ifndef LAYERBLOCKING_H
#define LAYERBLOCKING_H

#include <QRect>
#include <vector>

#include "layer_clipboard/clipboard.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class BlockingGraphicLayer;
}

namespace LayerClipboard {

//////////////////////////////////////////////////////////////////////////////
//  Blocking class
//////////////////////////////////////////////////////////////////////////////

// TODO rename it with a more specific name
class Blocking : public Clipboard
{
public:
    Blocking(const QRect&, const std::vector<uint8_t>&);
    Blocking(QRect&&, std::vector<uint8_t>&&);

    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override;

private:
    QRect m_clip;
    std::vector<std::uint8_t> m_content;
};

} // namespace LayerClipboard

#endif // LAYERBLOCKING_H
