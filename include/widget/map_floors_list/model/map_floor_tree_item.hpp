#ifndef MAPFLOORTREEITEM_H
#define MAPFLOORTREEITEM_H

#include "widget/map_floors_list/model/map_tree_item.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Floor;
} // namespace Editor

namespace Widget {
namespace MapFloorsList {
namespace Model {

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeItem class
//////////////////////////////////////////////////////////////////////////////

class MapFloorTreeItem : public MapTreeItem {
public:
    MapFloorTreeItem(Editor::Floor&, std::size_t index);
    QVariant data(int role = Qt::UserRole + 1) const override;
    void toggle() override;
    void setVisible(bool) override;
    void setSelected() override;
private:
    Editor::Floor& m_editorFloor;
    std::size_t m_index;
};
} // namespace Model
} // namespace MapFloorsList
} // namespace Widget

#endif // MAPFLOORTREEITEM_H
