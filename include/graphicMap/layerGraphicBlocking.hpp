#ifndef BLOCKINGGRAPHICLAYER_H
#define BLOCKINGGRAPHICLAYER_H

#include "graphicMap/layerGraphic.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class BlockingLayer;
} // namespace Editor

namespace GraphicMap {

//////////////////////////////////////////////////////////////////////////////
//  BlockingGraphicLayer class
//////////////////////////////////////////////////////////////////////////////

class BlockingGraphicLayer : public MapSceneLayer
{
    Q_OBJECT
public:
    explicit BlockingGraphicLayer(Editor::BlockingLayer&, int zValue);

    Editor::BlockingLayer& layer() { return m_blockingLayer; }
    bool tile(quint16, quint16) const;

    void toggleTile(quint16, quint16);
    void setTile(quint16, quint16, bool);

public slots:
    void setSelected() override;

signals:
    void layerSelected(GraphicMap::BlockingGraphicLayer*);

private:
    Editor::BlockingLayer& m_blockingLayer;
};
} // namespace GraphicMap

#endif // BLOCKINGGRAPHICLAYER_H
