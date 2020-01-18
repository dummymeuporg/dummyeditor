#ifndef LAYERCLIPBOARDVISIBLE_H
#define LAYERCLIPBOARDVISIBLE_H

#include <cstdint>
#include <utility>
#include <vector>

#include <QRect>

#include "layer_clipboard/clipboard.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace GraphicMap {
class VisibleGraphicLayer;
}

namespace LayerClipboard {

//////////////////////////////////////////////////////////////////////////////
//  Blocking class
//////////////////////////////////////////////////////////////////////////////

// TODO rename it with a more specific name
class Visible : public Clipboard
{
public:
    Visible(const QRect&, const std::vector<std::pair<int8_t, int8_t>>&);
    Visible(QRect&&, std::vector<std::pair<int8_t, int8_t>>&&);

    void visitGraphicLayer(GraphicMap::VisibleGraphicLayer&) override;
    void visitGraphicLayer(GraphicMap::BlockingGraphicLayer&) override
    {
        throw GraphicMap::GraphicLayerNotSupported();
    }
    void visitGraphicLayer(GraphicMap::EventsGraphicLayer&) override
    {
        throw GraphicMap::GraphicLayerNotSupported();
    }

private:
    QRect m_clip;
    std::vector<std::pair<int8_t, int8_t>> m_content;
};

} // namespace LayerClipboard

#endif // LAYERCLIPBOARDVISIBLE_H
