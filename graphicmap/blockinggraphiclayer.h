#pragma once

#include <QtGlobal>
#include <QVector>

#include "graphicmap/graphiclayer.h"

namespace Dummy {
    class BlockingLayer;
}

namespace GraphicMap {
    class BlockingCrossItem;
    class MapGraphicsScene;
    class BlockingGraphicLayer : public GraphicLayer
    {
    public:
        BlockingGraphicLayer(MapGraphicsScene&, Dummy::BlockingLayer&);
        virtual ~BlockingGraphicLayer() override;
        virtual void removeTile(quint16, quint16) override;
        void toggleTile(quint16, quint16);
    private:
        void _drawCross(int, quint16, quint16);
        Dummy::BlockingLayer& m_blockingLayer;
        QVector<BlockingCrossItem*> m_crossItems;
    };
}
