#pragma once

#include <QtGlobal>
#include <QVector>

#include "graphicmap/graphiclayer.hpp"

namespace Dummy {
    class BlockingLayer;
}

namespace GraphicMap {
    class BlockingSquareItem;
    class MapGraphicsScene;
    class MapSceneLayer;
    class BlockingGraphicLayer : public GraphicLayer
    {
    public:
        BlockingGraphicLayer(MapGraphicsScene&, Dummy::BlockingLayer&);
        virtual ~BlockingGraphicLayer() override;
        virtual MapSceneLayer& removeTile(quint16, quint16);
        void toggleTile(quint16, quint16);
        void setTile(quint16, quint16, bool);
    private:
        void _draw(int, quint16, quint16);
        Dummy::BlockingLayer& m_blockingLayer;
        QVector<BlockingSquareItem*> m_crossItems;
    };
}
