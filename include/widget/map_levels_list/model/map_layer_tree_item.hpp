#pragma once

#include <cstdint>

#include "widget/map_levels_list/model/map_tree_item.hpp"

namespace Editor {
class GraphicLayer;
class Map;
} // namespace Editor

namespace Widget {
namespace MapLevelsList {
namespace Model {
class MapLayerTreeItem : public MapTreeItem {
public:
    MapLayerTreeItem(std::int8_t);
private:
    std::int8_t m_position;
};
} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
