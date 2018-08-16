#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include "dummy/layer.h"
#include "graphicmap/graphiclayer.h"

namespace GraphicMap {
    // Forward declaration:
    class MapGraphicsScene;

    class VisibleGraphicLayer : public GraphicLayer {

    public:
        VisibleGraphicLayer(MapGraphicsScene&, Dummy::Layer&,
                            const QPixmap&, int zValue);
        virtual ~VisibleGraphicLayer() override;
        inline const QPixmap& chipsetPixmap() const {
            return m_chipsetPixmap;
        }

        inline const Dummy::Layer& layer() const {
            return m_layer;
        }

        inline const QVector<QGraphicsPixmapItem*>& layerItems() const {
            return m_layerItems;
        }

        VisibleGraphicLayer& setTile(quint16 x,
                                     quint16 y,
                                     qint16 chipsetX,
                                     qint16 chipsetY);

        VisibleGraphicLayer& setChipsetPixmap(const QPixmap*);

        VisibleGraphicLayer& setOpacity(qreal);

        virtual void removeTile(quint16, quint16) override;

    private:
        Dummy::Layer& m_layer;
        const QPixmap& m_chipsetPixmap;
        QVector<QGraphicsPixmapItem*> m_layerItems;
        int m_zValue;
    };
}
