#pragma once

#include <cstdint>

#include "widget/map_levels_list/model/map_tree_item.hpp"

namespace Editor {
class Layer;
} // namespace Editor

namespace Widget {
namespace MapLevelsList {
namespace Model {
class MapLayerTreeItem : public MapTreeItem {
public:
    void toggle() override;
    virtual Editor::Layer& layer() = 0;
};
} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
