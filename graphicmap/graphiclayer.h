#pragma once

#include <QtGlobal>
#include <QVector>

class QGraphicsItem;

namespace GraphicMap {

    class MapGraphicsScene;

    class GraphicLayer
    {
    public:
        GraphicLayer(MapGraphicsScene&);
        virtual ~GraphicLayer();

        virtual void removeTile(quint16, quint16) = 0;

        inline const QVector<QGraphicsItem*>& layerItems() const {
            return m_layerItems;
        }

        GraphicLayer& setOpacity(qreal);


    protected:
        MapGraphicsScene& m_mapGraphicsScene;
        QVector<QGraphicsItem*> m_layerItems;
    };
}
