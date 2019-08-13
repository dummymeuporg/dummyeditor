#pragma once

#include <cstdint>

#include "widget/map_floors_list/model/map_layer_tree_item.hpp"

namespace Editor {
class BlockingLayer;
class Map;
} // namespace Editor

namespace Widget {
namespace MapFloorsList {
namespace Model {
class MapBlockingLayerTreeItem : public MapLayerTreeItem {
public:
    MapBlockingLayerTreeItem(Editor::BlockingLayer&);
    Editor::Layer& layer() override;
    QVariant data(int role = Qt::UserRole + 1) const override;
    void setSelected() override;
private:
    Editor::BlockingLayer& m_blockingLayer;
};
} // namespace Model
} // namespace MapFloorsList
} // namespace Widget
