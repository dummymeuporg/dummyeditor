#pragma once
#include <memory>
#include <QGraphicsScene>
#include <QPixmap>

#include "graphicmap/graphiclayer.hpp"

namespace DrawingTool {
namespace Graphic {
class Pen;
} // namespace Graphic
} // namespace DrawingTool

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
                        int);
    ~VisibleGraphicLayer() override;
    inline const QPixmap& chipsetPixmap() const {
        return m_chipsetPixmap;
    }

    inline const Editor::GraphicLayer& layer() const {
        return m_graphicLayer;
    }

    VisibleGraphicLayer& setTile(quint16 x,
                                 quint16 y,
                                 qint16 chipsetX,
                                 qint16 chipsetY);

    VisibleGraphicLayer& setChipsetPixmap(const QPixmap*);

    virtual MapSceneLayer& removeTile(quint16, quint16) override;

    Editor::Layer& editorLayer() override;

    std::unique_ptr<DrawingTool::Graphic::Pen> getGraphicPen();


private:
    Editor::GraphicLayer& m_graphicLayer;
    const QPixmap& m_chipsetPixmap;
};
} // namespace GraphicMap
