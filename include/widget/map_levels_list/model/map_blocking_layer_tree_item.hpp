#pragma once

#include <cstdint>

#include "widget/map_levels_list/model/map_layer_tree_item.hpp"

namespace Editor {
class GraphicLayer;
class Map;
} // namespace Editor

namespace Widget {
namespace MapLevelsList {
namespace Model {
class MapGraphicLayerTreeItem : public MapLayerTreeItem {
public:
    MapGraphicLayerTreeItem(std::int8_t);
    void toggle() override;
private:
    std::int8_t m_position;
};
} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
