#pragma once

#include <QtGlobal>
#include <QVector>

#include "graphicmap/mapscenelayer.hpp"

class QGraphicsItem;

namespace GraphicMap {

    class MapGraphicsScene;

    class GraphicLayer : public MapSceneLayer
    {
    public:
        GraphicLayer(MapGraphicsScene&);
        virtual ~GraphicLayer() override;

        inline const QVector<QGraphicsItem*>& layerItems() const {
            return m_layerItems;
        }

        MapSceneLayer& setOpacity(qreal) override;


    protected:
        QVector<QGraphicsItem*> m_layerItems;
    };
}
