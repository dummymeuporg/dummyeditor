#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include "graphicmap/graphiclayer.hpp"

namespace Dummy {
namespace Core {
using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;
} // namespace Core
} // namespace Dummy

namespace GraphicMap {
// Forward declaration:
class MapGraphicsScene;

class VisibleGraphicLayer : public GraphicLayer {

public:
    VisibleGraphicLayer(MapGraphicsScene&,
                        Dummy::Core::GraphicLayer&,
                        const QPixmap&,
                        int zValue);
    virtual ~VisibleGraphicLayer() override;
    inline const QPixmap& chipsetPixmap() const {
        return m_chipsetPixmap;
    }

    inline const Dummy::Core::GraphicLayer& layer() const {
        return m_layer;
    }

    VisibleGraphicLayer& setTile(quint16 x,
                                 quint16 y,
                                 qint16 chipsetX,
                                 qint16 chipsetY);

    VisibleGraphicLayer& setChipsetPixmap(const QPixmap*);

    virtual MapSceneLayer& removeTile(quint16, quint16) override;

private:
    Dummy::Core::GraphicLayer& m_layer;
    const QPixmap& m_chipsetPixmap;
    int m_zValue;
};
} // namespace GraphicMap
