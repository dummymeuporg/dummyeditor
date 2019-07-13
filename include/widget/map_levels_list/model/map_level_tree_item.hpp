#pragma once

#include "widget/map_levels_list/model/map_tree_item.hpp"

namespace Editor {
class Level;
class Map;
} // namespace Editor

namespace Widget {
namespace MapLevelsList {
namespace Model {
class MapLevelTreeItem : public MapTreeItem {
public:
    MapLevelTreeItem(Editor::Level&, std::size_t index);
    QVariant data(int role = Qt::UserRole + 1) const override;
    void toggle() override;
    void setVisible(bool) override;
    void setSelected() override;
private:
    Editor::Level& m_editorLevel;
    std::size_t m_index;
};
} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
