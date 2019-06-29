#pragma once

#include <cstdint>

#include "widget/map_levels_list/model/map_layer_tree_item.hpp"

namespace Editor {
class BlockingLayer;
class Map;
} // namespace Editor

namespace Widget {
namespace MapLevelsList {
namespace Model {
class MapBlockingLayerTreeItem : public MapLayerTreeItem {
public:
    MapBlockingLayerTreeItem(Editor::BlockingLayer&);
    Editor::Layer& layer() override;
private:
    Editor::BlockingLayer& m_blockingLayer;
};
} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
