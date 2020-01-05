#ifndef MAPFLOORTREEITEM_H
#define MAPFLOORTREEITEM_H

#include "widget_mapFloorsList/map_tree_item.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Floor;
} // namespace Editor

namespace MapFloorsList {

//////////////////////////////////////////////////////////////////////////////
//  MapFloorTreeItem class
// This class is the model (data) of a floor (containing several layers)
//////////////////////////////////////////////////////////////////////////////

class FloorTreeItem : public MapTreeItem
{
public:
    FloorTreeItem(Editor::Floor& floor, std::size_t index);

    QVariant data(int role = Qt::UserRole + 1) const override;

    void toggle() override;
    void setVisible(bool) override;
    void setSelected() override;

private:
    void updateVisibilityIcon();

private:
    Editor::Floor& m_editorFloor;
    std::size_t m_index;
};

} // namespace MapFloorsList

#endif // MAPFLOORTREEITEM_H
