#pragma once

#include <QtGlobal>

#include "graphicmap/graphiclayer.h"

namespace Dummy {
    class BlockingLayer;
}

namespace GraphicMap {

    class MapGraphicsScene;
    class BlockingGraphicLayer : public GraphicLayer
    {
    public:
        BlockingGraphicLayer(MapGraphicsScene&, Dummy::BlockingLayer&);
        virtual ~BlockingGraphicLayer() override;
        virtual void removeTile(quint16, quint16) override;
    private:

    };
}
