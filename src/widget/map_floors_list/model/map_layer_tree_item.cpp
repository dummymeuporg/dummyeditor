#include "widget/map_floors_list/model/map_layer_tree_item.hpp"

#include "editor/layer.hpp"

namespace Widget {
namespace MapFloorsList {
namespace Model {

void MapLayerTreeItem::toggle() {
    setVisible(!layer().visible());
}

void MapLayerTreeItem::setVisible(bool visible) {
    layer().setVisible(visible);
    if (layer().visible()) {
        setIcon(QIcon(":/icons/icon_eye.png"));
    } else {
        setIcon(QIcon(":/icons/icon_eye_crossed.png"));
    }
}

} // namespace Model
} // namespace MapFloorsList
} // namespace Widget
