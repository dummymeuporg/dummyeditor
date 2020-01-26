#ifndef LAYERBLOCKING_H
#define LAYERBLOCKING_H

#include <QRect>
#include <cstdint>
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
    explicit Blocking(const QRect&, const std::vector<uint8_t>&);
    explicit Blocking(QRect&&, std::vector<uint8_t>&&);

    void paste(GraphicMap::BlockingGraphicLayer&);

private:
    QRect m_clip;
    std::vector<uint8_t> m_content;
};

} // namespace LayerClipboard

#endif // LAYERBLOCKING_H
