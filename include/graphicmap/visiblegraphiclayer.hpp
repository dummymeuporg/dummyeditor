#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include "graphicmap/graphiclayer.hpp"

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

        VisibleGraphicLayer& setTile(quint16 x,
                                     quint16 y,
                                     qint16 chipsetX,
                                     qint16 chipsetY);

        VisibleGraphicLayer& setChipsetPixmap(const QPixmap*);

        virtual MapSceneLayer& removeTile(quint16, quint16) override;

    private:
        Dummy::Layer& m_layer;
        const QPixmap& m_chipsetPixmap;
        int m_zValue;
    };
}
