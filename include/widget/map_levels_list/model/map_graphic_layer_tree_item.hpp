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
    MapGraphicLayerTreeItem(std::int8_t, Editor::GraphicLayer&);
    Editor::Layer& layer() override;
    QVariant data(int role = Qt::UserRole + 1) const override;
    void setSelected() override;

private:
    std::int8_t m_position;
    Editor::GraphicLayer& m_graphicLayer;
};
} // namespace Model
} // namespace MapLevelsList
} // namespace Widget
