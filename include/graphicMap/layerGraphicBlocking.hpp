#ifndef BLOCKINGGRAPHICLAYER_H
#define BLOCKINGGRAPHICLAYER_H

#include "graphicMap/layerGraphic.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class BlockingLayer;
} // namespace Editor

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  BlockingGraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class BlockingGraphicLayer : public MapSceneLayer
{
    Q_OBJECT
public:
    BlockingGraphicLayer(Editor::BlockingLayer&, int zValue);
    std::shared_ptr<LayerClipboard::Clipboard> getClipboardRegion(const QRect& clip) override;
    Editor::BlockingLayer& layer() { return m_blockingLayer; }

    void toggleTile(quint16, quint16);
    void setTile(quint16, quint16, bool);

public slots:
    void setSelected() override;

signals:
    void layerSelected(GraphicMap::BlockingGraphicLayer*);

private:
    Editor::BlockingLayer& m_blockingLayer;
};
} // namespace GraphicMap

#endif // BLOCKINGGRAPHICLAYER_H
