#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include "dummy/layer.h"

namespace GraphicMap {
    // Forward declaration:
    class MapGraphicsScene;

    class GraphicLayer {

    public:
        GraphicLayer(MapGraphicsScene&, Dummy::Layer&,
                     const QPixmap&, int zValue);
        virtual ~GraphicLayer();
        inline const QPixmap& chipsetPixmap() const {
            return m_chipsetPixmap;
        }

        inline const Dummy::Layer& layer() const {
            return m_layer;
        }

        inline const QVector<QGraphicsPixmapItem*>& layerItems() const {
            return m_layerItems;
        }

        GraphicLayer& setTile(quint16 x,
                              quint16 y,
                              qint16 chipsetX,
                              qint16 chipsetY);

        GraphicLayer& setChipsetPixmap(const QPixmap*);

        GraphicLayer& setOpacity(qreal);

    private:
        MapGraphicsScene& m_mapGraphicsScene;
        Dummy::Layer& m_layer;
        const QPixmap& m_chipsetPixmap;
        QVector<QGraphicsPixmapItem*> m_layerItems;
        int m_zValue;
    };
}
