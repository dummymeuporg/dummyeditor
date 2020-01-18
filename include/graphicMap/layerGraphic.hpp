#ifndef GRAPHICLAYER_H
#define GRAPHICLAYER_H

#include <QObject>
#include <memory>

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
class MapGraphicsScene;

//////////////////////////////////////////////////////////////////////////////
//  GraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class MapSceneLayer : public QObject
{
    Q_OBJECT
public:
    MapSceneLayer(MapGraphicsScene&, int zIndex);

    MapGraphicsScene& mapGraphicsScene() { return m_mapGraphicsScene; }

    virtual Editor::Layer& editorLayer()                           = 0;
    virtual std::vector<DrawingTools::DrawingTool*> drawingTools() = 0;
    virtual void accept(GraphicLayerVisitor&)                      = 0;
    virtual std::shared_ptr<LayerClipboard::Clipboard>
    getClipboardRegion(const QRect& clip) = 0;

public slots:
    void setVisibility(bool);
    void setSelected();

signals:
    void layerSelected(GraphicMap::MapSceneLayer*);

protected:
    std::vector<QGraphicsItem*>& layerItems() { return m_layerItems; }
    int zIndex() { return m_zIndex; }

private:
    MapGraphicsScene& m_mapGraphicsScene;
    int m_zIndex;
    std::vector<QGraphicsItem*> m_layerItems;
};
} // namespace GraphicMap

#endif // GRAPHICLAYER_H
