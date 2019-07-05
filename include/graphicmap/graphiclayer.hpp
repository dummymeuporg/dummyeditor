#pragma once

#include <QtGlobal>
#include <QVector>

#include "graphicmap/mapscenelayer.hpp"

class QGraphicsItem;

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

signals:
    void layerSelected();

public slots:
    void setVisibility(bool);
protected:
    QVector<QGraphicsItem*> m_layerItems;
};
} // namespace GraphicMap
