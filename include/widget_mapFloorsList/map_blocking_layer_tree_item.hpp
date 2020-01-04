#ifndef MAPBLOCKINGLAYERTREEITEM_H
#define MAPBLOCKINGLAYERTREEITEM_H

#include "widget_mapFloorsList/map_layer_tree_item.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class BlockingLayer;
} // namespace Editor

namespace MapFloorsList {

//////////////////////////////////////////////////////////////////////////////
//  MapBlockingLayerTreeItem class
//////////////////////////////////////////////////////////////////////////////

class MapBlockingLayerTreeItem : public MapLayerTreeItem
{
public:
    MapBlockingLayerTreeItem(Editor::BlockingLayer&);
    Editor::Layer& layer() override;
    QVariant data(int role = Qt::UserRole + 1) const override;
    void setSelected() override;

private:
    Editor::BlockingLayer& m_blockingLayer;
};

} // namespace MapFloorsList

#endif // MAPBLOCKINGLAYERTREEITEM_H
