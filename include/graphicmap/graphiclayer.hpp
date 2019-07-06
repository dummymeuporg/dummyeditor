#pragma once

#include <memory>

#include <QtGlobal>
#include <QVector>

#include "graphicmap/mapscenelayer.hpp"

class QGraphicsItem;

namespace DrawingTool {
class DrawingTool;
} // namespace DrawingTool

namespace Editor {
class Layer;
} // namespace Editor

namespace GraphicMap {

class MapGraphicsScene;

class GraphicLayer : public MapSceneLayer
{
    Q_OBJECT
public:
    GraphicLayer(MapGraphicsScene&, int);

    inline const QVector<QGraphicsItem*>& layerItems() const {
        return m_layerItems;
    }

    virtual Editor::Layer& editorLayer() = 0;

    virtual std::vector<DrawingTool::DrawingTool*> drawingTools() = 0;

signals:
    void layerSelected(GraphicMap::GraphicLayer*);

public slots:
    void setVisibility(bool);
    void setSelected();
protected:
    QVector<QGraphicsItem*> m_layerItems;
};
} // namespace GraphicMap
