#include "editor/blocking_layer.hpp"

#include "widget/map_levels_list/model/map_blocking_layer_tree_item.hpp"

namespace Widget {
namespace MapLevelsList {
namespace Model {

MapBlockingLayerTreeItem::MapBlockingLayerTreeItem(
    Editor::BlockingLayer& blockingLayer
) : m_blockingLayer(blockingLayer)
{}

Editor::Layer& MapBlockingLayerTreeItem::layer() {
    return m_blockingLayer;
}

} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
