#ifndef VISIBLEGRAPHICLAYER_H
#define VISIBLEGRAPHICLAYER_H

#include <QGraphicsScene>
#include <QPixmap>
#include <memory>

#include "drawingTool/graphicEraser.hpp"
#include "drawingTool/graphicPen.hpp"
#include "drawingTool/graphicRectangle.hpp"

#include "graphicMap/layerGraphic.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class GraphicLayer;
} // namespace Editor

namespace GraphicMap {
class MapGraphicsScene;

//////////////////////////////////////////////////////////////////////////////
//  VisibleGraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class VisibleGraphicLayer : public MapSceneLayer
{
public:
    VisibleGraphicLayer(Editor::GraphicLayer&, MapGraphicsScene&,
                        const QPixmap&, int);
    ~VisibleGraphicLayer() override;
    const QPixmap& chipsetPixmap() const { return m_chipsetPixmap; }
    const Editor::GraphicLayer& layer() const { return m_graphicLayer; }

    VisibleGraphicLayer& setTile(quint16 x, quint16 y, qint16 chipsetX,
                                 qint16 chipsetY);
    VisibleGraphicLayer& setChipsetPixmap(const QPixmap*);

    //virtual MapSceneLayer& removeTile(quint16, quint16) override;

    Editor::Layer& editorLayer() override;

    std::vector<DrawingTools::DrawingTool*> drawingTools() override;

    std::shared_ptr<LayerClipboard::Clipboard>
    getClipboardRegion(const QRect& clip) override;

    void accept(GraphicLayerVisitor&) override;

private:
    Editor::GraphicLayer& m_graphicLayer;
    const QPixmap& m_chipsetPixmap;
};
} // namespace GraphicMap

#endif // VISIBLEGRAPHICLAYER_H
