#pragma once

#include <cstdint>

#include "widget/map_floors_list/model/map_tree_item.hpp"

namespace Editor {
class Layer;
} // namespace Editor

namespace Widget {
namespace MapFloorsList {
namespace Model {
class MapLayerTreeItem : public MapTreeItem {
public:
    void toggle() override;
    void setVisible(bool) override;
    virtual Editor::Layer& layer() = 0;
};
} // namespace Model
} // namespace MapFloorsList
} // namespace Widget
