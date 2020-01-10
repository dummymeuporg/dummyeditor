#ifndef GRAPHICLAYER_H
#define GRAPHICLAYER_H

#include <memory>

#include "graphicMap/mapSceneLayer.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

class QGraphicsItem;

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTools

namespace Editor {
class Layer;
} // namespace Editor

namespace LayerClipboard {
class Clipboard;
} // namespace LayerClipboard

namespace GraphicMap {
class GraphicLayerVisitor;

//////////////////////////////////////////////////////////////////////////////
//  GraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class GraphicLayer : public MapSceneLayer
{
    Q_OBJECT
public:
    GraphicLayer(MapGraphicsScene&, int);

    //const QVector<QGraphicsItem*>& layerItems() const { return m_layerItems; }
    virtual Editor::Layer& editorLayer()                           = 0;
    virtual std::vector<DrawingTools::DrawingTool*> drawingTools() = 0;
    virtual void accept(GraphicLayerVisitor&)                      = 0;
    virtual std::shared_ptr<LayerClipboard::Clipboard>
    getClipboardRegion(const QRect& clip) = 0;

signals:
    void layerSelected(GraphicMap::GraphicLayer*);

public slots:
    void setVisibility(bool);
    void setSelected();

protected:
  std::vector<QGraphicsItem*> m_layerItems;
};
} // namespace GraphicMap

#endif // GRAPHICLAYER_H
