#ifndef VISIBLEGRAPHICLAYER_H
#define VISIBLEGRAPHICLAYER_H

#include <QGraphicsScene>
#include <QPixmap>
#include <memory>

#include "graphicMap/layerGraphic.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class GraphicLayer;
} // namespace Editor

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  VisibleGraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class VisibleGraphicLayer : public MapSceneLayer
{
    Q_OBJECT
public:
    explicit VisibleGraphicLayer(Editor::GraphicLayer&, const QPixmap&, int);

    const QPixmap& chipsetPixmap() const { return m_chipsetPixmap; }
    Editor::GraphicLayer& layer() { return m_graphicLayer; }

    void setTile(quint16 x, quint16 y, qint16 chipsetX, qint16 chipsetY);
    void setChipsetPixmap(const QPixmap*);

public slots:
    void setSelected() override;

signals:
    void layerSelected(GraphicMap::VisibleGraphicLayer*);

private:
    Editor::GraphicLayer& m_graphicLayer;
    const QPixmap& m_chipsetPixmap;
};
} // namespace GraphicMap

#endif // VISIBLEGRAPHICLAYER_H
