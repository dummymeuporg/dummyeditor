#pragma once

#include <QGraphicsScene>
#include <QPixmap>

#include "graphicmap/graphiclayer.hpp"

namespace Editor {
class GraphicLayer;
} // namespace Editor

namespace Dummy {
namespace Core {
class GraphicLayer;
} // namespace Core
} // namespace Dummy


namespace GraphicMap {
// Forward declaration:
class MapGraphicsScene;

class VisibleGraphicLayer : public GraphicLayer {

public:
    VisibleGraphicLayer(MapGraphicsScene&,
                        Editor::GraphicLayer&,
                        const QPixmap&,
                        int zValue);
    ~VisibleGraphicLayer() override;
    inline const QPixmap& chipsetPixmap() const {
        return m_chipsetPixmap;
    }

    inline const Editor::GraphicLayer& layer() const {
        return m_layer;
    }

    VisibleGraphicLayer& setTile(quint16 x,
                                 quint16 y,
                                 qint16 chipsetX,
                                 qint16 chipsetY);

    VisibleGraphicLayer& setChipsetPixmap(const QPixmap*);

    virtual MapSceneLayer& removeTile(quint16, quint16) override;

private:
    Editor::GraphicLayer& m_layer;
    const QPixmap& m_chipsetPixmap;
    int m_zValue;
};
} // namespace GraphicMap
