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
class BlockingSquareItem;

//////////////////////////////////////////////////////////////////////////////
//  BlockingGraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class BlockingGraphicLayer : public GraphicLayer
{
public:
    BlockingGraphicLayer(Editor::BlockingLayer&, MapGraphicsScene&, int zValue);
    ~BlockingGraphicLayer() override;

    const Editor::BlockingLayer& layer() const { return m_blockingLayer; }
    Editor::Layer& editorLayer() override;

    // MapSceneLayer& removeTile(quint16, quint16) override;
    void toggleTile(quint16, quint16);
    void setTile(quint16, quint16, bool);

    std::vector<DrawingTools::DrawingTool*> drawingTools() override;
    void accept(GraphicLayerVisitor&) override;

    std::shared_ptr<LayerClipboard::Clipboard>
    getClipboardRegion(const QRect& clip) override;

private:
    void erase(int, quint16, quint16);
    void draw(int, quint16, quint16);

private:
    Editor::BlockingLayer& m_blockingLayer;
};
} // namespace GraphicMap

#endif // BLOCKINGGRAPHICLAYER_H
