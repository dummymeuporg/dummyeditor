#ifndef MAPGRAPHICLAYERTREEITEM_H
#define MAPGRAPHICLAYERTREEITEM_H

#include "widget_mapFloorsList/map_layer_tree_item.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class GraphicLayer;
} // namespace Editor

namespace MapFloorsList {

//////////////////////////////////////////////////////////////////////////////
//  MapGraphicLayerTreeItem class
//////////////////////////////////////////////////////////////////////////////

class MapGraphicLayerTreeItem : public MapLayerTreeItem {
public:
    MapGraphicLayerTreeItem(std::int8_t, Editor::GraphicLayer&);
    Editor::Layer& layer() override;
    QVariant data(int role = Qt::UserRole + 1) const override;
    void setSelected() override;

private:
    std::int8_t m_position;
    Editor::GraphicLayer& m_graphicLayer;
};
} // namespace MapFloorsList

#endif // MAPGRAPHICLAYERTREEITEM_H
