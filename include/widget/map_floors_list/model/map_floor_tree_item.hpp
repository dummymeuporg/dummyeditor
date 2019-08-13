#pragma once

#include "widget/map_floors_list/model/map_tree_item.hpp"

namespace Editor {
class Floor;
class Map;
} // namespace Editor

namespace Widget {
namespace MapFloorsList {
namespace Model {
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
