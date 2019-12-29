#pragma once

#include <memory>

#include <QtGlobal>
#include <QVector>

#include "graphicmap/mapscenelayer.hpp"

class QGraphicsItem;

namespace DrawingTools {
class DrawingTool;
} // namespace DrawingTool

namespace Editor {
class Layer;
} // namespace Editor

namespace LayerClipboard {
class Clipboard;
} // namespace LayerClipboard

namespace GraphicMap {

class MapGraphicsScene;
class GraphicLayerVisitor;

class GraphicLayer : public MapSceneLayer
{
    Q_OBJECT
public:
    GraphicLayer(MapGraphicsScene&, int);

    inline const QVector<QGraphicsItem*>& layerItems() const {
        return m_layerItems;
    }

    virtual Editor::Layer& editorLayer() = 0;

    virtual std::vector<DrawingTools::DrawingTool*> drawingTools() = 0;

    virtual void accept(GraphicLayerVisitor&) = 0;

    virtual std::shared_ptr<LayerClipboard::Clipboard>
    getClipboardRegion(const QRect& clip) = 0;

signals:
    void layerSelected(GraphicMap::GraphicLayer*);

public slots:
    void setVisibility(bool);
    void setSelected();
protected:
    QVector<QGraphicsItem*> m_layerItems;
};
} // namespace GraphicMap
