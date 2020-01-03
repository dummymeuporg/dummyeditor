#ifndef MAPLAYERTREEITEM_H
#define MAPLAYERTREEITEM_H

#include "widget/map_floors_list/model/map_tree_item.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Layer;
} // namespace Editor

namespace Widget {
namespace MapFloorsList {
namespace Model {

//////////////////////////////////////////////////////////////////////////////
//  MapLayerTreeItem class
//////////////////////////////////////////////////////////////////////////////

class MapLayerTreeItem : public MapTreeItem {
public:
    void toggle() override;
    void setVisible(bool) override;
    virtual Editor::Layer& layer() = 0;
};
} // namespace Model
} // namespace MapFloorsList
} // namespace Widget

#endif // MAPLAYERTREEITEM_H
